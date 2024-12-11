import java.util.Scanner;
import java.io.IOException;
import java.io.File;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

class Day02 implements Day{
    static final String OFFICIAL_INPUT_PATH = "./Day02-input";

	public static void main(String[] args) {
        Day02 day = new Day02();
        day.printResults(
            OFFICIAL_INPUT_PATH,
            "Count valid sleds",
            "Count valid toboggans"
        );
	}
	
    /* Part 1 */
	static int charFrequency(String s, char target) {
		int result = 0;
        // cursed, I know ;)
		for(char c: s.toCharArray())
			if(c == target)
				++result;
		return result;
	}
	
	public int part1(String path) throws IOException {
        Scanner fp = new Scanner(new File(path));
        Pattern p = Pattern.compile("(\\d+)-(\\d+) ([a-z]{1}): ([a-z]+)");
        int result = 0;
        do {
            String line = fp.nextLine();
            Matcher m = p.matcher(line);
            if(!m.matches())
                break;
            int low = Integer.parseInt(m.group(1));
            int high = Integer.parseInt(m.group(2));
            int n = charFrequency(m.group(4),m.group(3).charAt(0));
            if(low <= n && n <= high)
                ++result;
        } while(fp.hasNextLine());
        fp.close();
        return result;
	}
	
    /* Part 2 */
	static boolean isTobogganValid(
			int i, int j, char c, String password) {
		return password.length() >= j && 
			(password.charAt(i-1) == c ^ password.charAt(j-1) == c);
	}

	public int part2(String path) throws IOException {
        Scanner fp = new Scanner(new File(path));
        Pattern p = Pattern.compile("(\\d+)-(\\d+) ([a-z]{1}): ([a-z]+)");
        int result = 0;
        do {
            String line = fp.nextLine();
            Matcher m = p.matcher(line);
            if(!m.matches())
                break;
            int low = Integer.parseInt(m.group(1));
            int high = Integer.parseInt(m.group(2));
            if(isTobogganValid(low,high,m.group(3).charAt(0),m.group(4)))
                ++result;
        } while(fp.hasNextLine());
        fp.close();
        return result;
	}
}
