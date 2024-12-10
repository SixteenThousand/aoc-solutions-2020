import Text.Printf

readInts :: String -> [Int]
readInts s = [read line | line <- (lines s)]

prod :: [Int] -> Int
prod [] = 1
prod (x:xs) = x * (prod xs)


-- Part 1
findSumPair :: [Int] -> Int -> [Int]
findSumPair [] sum = []
findSumPair [_] sum = []
findSumPair (x:xs) sum = if (sum-x) `elem` xs
    then [x,sum-x]
    else findSumPair xs sum

part1 :: String -> Int
part1 input = prod $ findSumPair (readInts input) 2020

-- Part 2
findSumTriplet :: [Int] -> Int -> [Int]
findSumTriplet [] sum = []
findSumTriplet [_] sum = []
findSumTriplet [_,_] sum = []
findSumTriplet (x:xs) sum = if (findSumPair xs $ sum-x) /= []
    then x:(findSumPair xs (sum-x))
    else findSumTriplet xs sum

part2 :: String -> Int
part2 input = prod $ findSumTriplet (readInts input) 2020


main = 
    readFile "./Day01-input"
    >>= \input -> (
        printf "\x1b[3mPart 1\x1b[0m\n  >>\x1b[1m%d\x1b[0m<<\n" (part1 input)
        >> return input
    )
    >>= \input -> 
        printf "\x1b[3mPart 2\x1b[0m\n  >>\x1b[1m%d\x1b[0m<<\n" (part2 input)
