using System;
using System.IO;
using System.Linq;

class Program
{
    private const string OldLine = @"            ""$output"": ""-MMD -o ${out} ${in}"",";
    private const string NewLine = @"            ""$output"": "" -o ${out} ${in}"",";

    static int Main(string[] args)
    {
        bool automaticmode = false;
        if (args.Length != 2)
        {
            Console.WriteLine("Usage: program.exe <directory_path> <filename>");
            Console.WriteLine("no arguments provided, attempting automatic mode...");
            automaticmode = true;
        }



        if (automaticmode)
        {
            string vscodePath;

            if (getVsCodePath(out vscodePath))
            {
                Console.WriteLine("Found vscode path: " + vscodePath);
                try
                {
                    int modifiedCount = ProcessFiles(vscodePath, "sdcc.model.json");
                    Console.WriteLine($"\nCompleted! Modified {modifiedCount} files.");
                    return 0;
                }
                catch (Exception ex)
                {
                    Console.WriteLine($"An error occurred: {ex.Message}");
                    return 1;
                }
                Console.WriteLine($"\nCompleted! Modified {modifiedCount} files.");
            }

            if (getVsCodeInsidersPath(out vscodePath))
            {
                Console.WriteLine("Found vscode path: " + vscodePath);
                try
                {
                    int modifiedCount = ProcessFiles(vscodePath, "sdcc.model.json");
                    Console.WriteLine($"\nCompleted! Modified {modifiedCount} files.");
                    return 0;
                }
                catch (Exception ex)
                {
                    Console.WriteLine($"An error occurred: {ex.Message}");
                    return 1;
                }
                Console.WriteLine($"\nCompleted! Modified {modifiedCount} files.");
            }
        }
        else
        {
            string directoryPath = args[0];
            string filename = args[1];

            if (!Directory.Exists(directoryPath))
            {
                Console.WriteLine($"Error: Directory '{directoryPath}' does not exist");
                return 1;
            }

            try
            {
                int modifiedCount = ProcessFiles(directoryPath, filename);
                Console.WriteLine($"\nCompleted! Modified {modifiedCount} files.");
                return 0;
            }
            catch (Exception ex)
            {
                Console.WriteLine($"An error occurred: {ex.Message}");
                return 1;
            }
        }

        return 0;
    }

    private static int ProcessFiles(string directoryPath, string filename)
    {
        int modifiedCount = 0;

        // Find all matching files recursively
        var files = Directory.GetFiles(directoryPath, filename, SearchOption.AllDirectories);

        foreach (var file in files)
        {
            Console.WriteLine($"Processing: {file}");
            if (ProcessFile(file))
            {
                modifiedCount++;
                Console.WriteLine($"Modified: {file}");
            }
        }

        return modifiedCount;
    }

    private static bool getVsCodePath(out string path)
    {
        //get the vscode paths .vscode or .vscode-insiders
        string vscodePath = Path.Combine(Environment.GetEnvironmentVariable("userprofile"), ".vscode", "extensions");

        if (Directory.Exists(vscodePath))
        {
            path = vscodePath;
            return true;
        }
        else
        {
            path = "";
            return false;
        }
    }

    private static bool getVsCodeInsidersPath(out string path)
    {

        //get the vscode paths .vscode or .vscode-insiders
        string vscodePath = Path.Combine(Environment.GetEnvironmentVariable("userprofile"), ".vscode-insiders", "extensions");
        if (Directory.Exists(vscodePath))
        {
            path = vscodePath;
            return true;
        }
        else
        {
            path = "";
            return false;
        }
    }


    private static bool ProcessFile(string filePath)
    {
        string tempPath = filePath + ".tmp";
        bool modified = false;

        try
        {
            // Read all lines and modify as needed
            var lines = File.ReadAllLines(filePath);
            for (int i = 0; i < lines.Length; i++)
            {
                if (lines[i] == OldLine)
                {
                    lines[i] = NewLine;
                    modified = true;
                }
            }

            // Only write if modifications were made
            if (modified)
            {
                File.WriteAllLines(tempPath, lines);
                File.Delete(filePath);
                File.Move(tempPath, filePath);
            }

            return modified;
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Error processing {filePath}: {ex.Message}");
            if (File.Exists(tempPath))
            {
                File.Delete(tempPath);
            }
            return false;
        }
    }
}