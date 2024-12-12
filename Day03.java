import java.util.Scanner;
import java.io.File;
import java.io.FileNotFoundException;
import java.util.List;

class Day03 implements Day {
    static final String OFFICIAL_INPUT_PATH = "./Day03-input";

	public static void main(String[] args) {
        Day03 day = new Day03();
        day.printResults(
            OFFICIAL_INPUT_PATH,
            "Count the no. of trees that are on a right 3 down 1 path",
            "Count the no. of trees on a short list of paths and multiply them"
        );
	}
	
    // Part 1
	static int numTreesOnPath(String inputPath, int right, int down)
            throws FileNotFoundException {
        Scanner fp = new Scanner(new File(inputPath));
        int lineIndex = 0;
		int row = 0;
		int col = 0;
		int result = 0;
        String line = fp.nextLine();
        int numCols = line.length();
        if(line.charAt(col) == '#') result++;
        row += down;
        col = (col+right) % numCols;
        while(fp.hasNextLine()) {
            lineIndex++;
            line = fp.nextLine();
            if(lineIndex == row) {
                if(line.charAt(col) == '#') result++;
                row += down;
                col = (col+right) % numCols;
            }
        }
        fp.close();
		return result;
	}

    public long part1(String inputPath) throws FileNotFoundException {
        return numTreesOnPath(inputPath, 3, 1);
    }

    // Part 2
	static long product(List<Integer> arr) {
		int result = 1;
		for(int x: arr) result *= x;
		return result;
	}

    public long part2(String inputPath) throws FileNotFoundException {
		int[][] slopes = new int[][] {{1,1}, {3,1}, {5,1}, {7,1}, {1,2}};
		int treeTotal;
		long result = 1;
		for(int[] slope: slopes) {
			treeTotal = numTreesOnPath(inputPath, slope[0], slope[1]);
			result *= treeTotal;
		}
        return result;
    }
}
