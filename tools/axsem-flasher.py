#!/usr/bin/env python3
import argparse
import os
import sys
import time
import serial
import serial.tools.list_ports
from tqdm import tqdm

class AxsemFlasher:
    def __init__(self, port, baudrate=38400, timeout=1):
        self.port = port
        self.baudrate = baudrate
        self.timeout = timeout
        self.serial = None
    
    def open(self):
        try:
            self.serial = serial.Serial(
                port=self.port,
                baudrate=self.baudrate,
                bytesize=serial.EIGHTBITS,
                parity=serial.PARITY_NONE,
                stopbits=serial.STOPBITS_ONE,
                timeout=self.timeout,
                xonxoff=False,
                rtscts=False,
                dsrdtr=False
            )
            return True
        except Exception as e:
            print(f"Error opening port {self.port}: {e}")
            return False
    
    def close(self):
        if self.serial and self.serial.is_open:
            self.serial.close()
    
    def set_boot_pin(self, state):
        self.serial.dtr = state
    
    def set_reset_pin(self, state):
        self.serial.rts = state
    
    def enter_boot_mode(self):
        print("Entering boot mode...")
        # Set boot pin high (DTR)
        self.set_reset_pin(False)
        self.set_boot_pin(True)
        
        # Toggle reset
        self.set_reset_pin(True)
        time.sleep(0.1)
        self.set_reset_pin(False)
        
        time.sleep(0.1)
        
        # Release boot pin
        self.set_boot_pin(False)
    
    def get_banner(self):
        self.serial.write(b"?")
        time.sleep(0.1)
        response = self.serial.readline().decode('utf-8', errors='ignore').strip()
        return response
    
    def validate_bootloader(self):
        print("Validating bootloader...")
        if not self.open():
            return False
        
        self.enter_boot_mode()
        banner = self.get_banner()
        print(f"Banner received: {banner}")
        
        if "Bootloader" in banner:
            print("Successfully entered bootloader!")
            return True
        
        print("Failed to enter bootloader")
        return False
    
    def erase_application(self):
        print("Erasing application...")
        self.serial.write(b"K")
        response = self.serial.readline().decode('utf-8', errors='ignore').strip()
        return "OK" in response
    
    def run_application(self):
        print("Running application...")
        self.serial.write(b"R")
        return True
    
    def program_hex_line(self, line):
        self.serial.write((line + '\n').encode())
        time.sleep(0.01)  # Small delay after writing each line
        return True
    
    def program_hex_file(self, hex_file_path):
        if not os.path.exists(hex_file_path):
            print(f"Error: Hex file not found: {hex_file_path}")
            return False
        
        with open(hex_file_path, 'r') as f:
            hex_lines = f.readlines()
        
        print(f"Programming {len(hex_lines)} lines...")
        for line in tqdm(hex_lines, desc="Programming", unit="lines"):
            self.program_hex_line(line.strip())
        
        return True
    
    def flash(self, hex_file_path):
        if not self.validate_bootloader():
            return False
        
        if not self.erase_application():
            print("Failed to erase application")
            self.close()
            return False
        
        print("Application erased")
        
        if not self.program_hex_file(hex_file_path):
            print("Failed to program hex file")
            self.close()
            return False
        
        print("Hex file programmed")
        time.sleep(0.1)
        
        self.run_application()
        time.sleep(0.1)
        
        print("Application running")
        self.close()
        return True

def list_ports():
    ports = list(serial.tools.list_ports.comports())
    if not ports:
        print("No serial ports found")
        return
    
    print("Available serial ports:")
    for port in ports:
        print(f"  {port.device}: {port.description}")

def main():
    parser = argparse.ArgumentParser(description='Axsem Hex File Flasher')
    parser.add_argument('hex_file', nargs='?', help='Path to the hex file')
    parser.add_argument('-p', '--port', help='Serial port')
    parser.add_argument('-b', '--baudrate', type=int, default=38400, help='Baudrate (default: 38400)')
    parser.add_argument('-l', '--list', action='store_true', help='List available serial ports')
    
    args = parser.parse_args()
    
    if args.list:
        list_ports()
        return 0
    
    if not args.hex_file or not args.port:
        parser.print_help()
        return 1
    
    flasher = AxsemFlasher(args.port, args.baudrate)
    success = flasher.flash(args.hex_file)
    
    return 0 if success else 1

if __name__ == "__main__":
    sys.exit(main())