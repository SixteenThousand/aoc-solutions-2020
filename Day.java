import java.io.FileNotFoundException;

interface Day {
    long part1(String inputPath) throws FileNotFoundException;

    long part2(String inputPath) throws FileNotFoundException;
    
    default void printResults(String inputPath, String msg1, String msg2) {
        try {
            System.out.printf(
                "\033[3;32mPart 1: %s\033[0m\n  >>\033[1;33m%d\033[0m<<\n",
                msg1,
                this.part1(inputPath)
            );
        } catch(FileNotFoundException err) {
            System.err.printf("Error reading file >>%s<<:\n",inputPath);
            System.err.println(err);
            System.exit(1);
        }
        try {
            System.out.printf(
                "\033[3;32mPart 2: %s\033[0m\n  >>\033[1;33m%d\033[0m<<\n",
                msg2,
                this.part2(inputPath)
            );
        } catch(FileNotFoundException err) {
            System.err.printf("Error reading file >>%s<<:\n",inputPath);
            System.err.println(err);
            System.exit(1);
        }
    }
}
