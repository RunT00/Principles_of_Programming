import Data.Char (toUpper, toLower)

square :: Int -> Int
square x = x * x

pyth :: Int -> Int -> Int
pyth x y = square x + square y

isTriple :: Int -> Int -> Int -> Bool
isTriple x y z = pyth x y == square z

isTripleAny :: Int -> Int -> Int -> Bool
isTripleAny x y z = pyth x y == square z || pyth x z == square y || pyth y z == square x

halfEvens :: [Int] -> [Int]
halfEvens xs = [if x `mod` 2 == 0 then x `div` 2 else x | x <- xs]

inRange :: Int -> Int -> [Int] -> [Int]
inRange x y nums = [num | num <- nums, num >= x, num <= y]

countPositives :: [Int] -> Int
countPositives xs = sum([1 | num <- xs, num > 0])

capitalised :: String -> String
capitalised "" = ""
capitalised (a : xs) = toUpper a : [toLower x | x <- xs]

toLowers :: String -> String
toLowers "" = ""
toLowers xs = [toLower x | x <- xs]

title :: [String] -> [String]
title [] = []
title (a : xss) = capitalised a : [if length xs >= 4 then capitalised xs else toLowers xs | xs <- xss]