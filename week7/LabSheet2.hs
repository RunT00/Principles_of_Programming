import Data.Char (toUpper, toLower, ord, chr)
import Data.ByteString (count)

inRange :: Int -> Int -> [Int] -> [Int]
inRange _ _ [] = []
inRange minVal maxVal (x:xs)
    | x >= minVal && x <= maxVal = x : inRange minVal maxVal xs
    | otherwise                  = inRange minVal maxVal xs

countPositives :: [Int] -> Int
countPositives [] = 0
countPositives (x:xs)
    | x > 0     = 1 + countPositives xs
    | otherwise = countPositives xs

capitalised :: String -> String
capitalised "" = ""
capitalised (x:xs) = toUpper x : lowerRest xs

lowerRest :: String -> String
lowerRest "" = ""
lowerRest (x:xs) = toLower x : lowerRest xs

title :: [String] -> [String]
title [] = []
title (xs:xss) = capitalised xs : formatRest xss

formatRest :: [String] -> [String]
formatRest [] = []
formatRest (xs:xss)
    | length xs >= 4 = capitalised xs : formatRest xss
    | otherwise      = lowerRest xs : formatRest xss

isort :: Ord a => [a] -> [a]
isort [] = []
isort (x:xs) = insert x (isort xs)

isortD :: Ord a => [a] -> [a]
isortD [] = []
isortD (x:xs) = insertD x (isortD xs)

isortDE :: Ord a => [a] -> [a]
isortDE [] = []
isortDE xs = isortD (delDup xs)

delDup :: Eq a => [a] -> [a]
delDup [] = []
delDup (x : xs)
    | x `elem` xs = delDup xs
    | otherwise   = x : delDup xs

insert :: Ord a => a -> [a] -> [a]
insert x [] = [x]
insert x (y:ys)
    | x <= y    = (x : y : ys)
    | otherwise = y : insert x ys

insertD :: Ord a => a -> [a] -> [a]
insertD x [] = [x]
insertD x (y:ys)
    | x >= y = (x : y : ys)
    | otherwise = y : insertD x ys

merge :: Ord a => [a] -> [a] -> [a]
merge [][] = []
merge (x:xs) (y:ys)
    | x <= y    = x : y : merge xs ys
    | otherwise = y : x : merge xs ys

rotor :: Int -> String -> String
rotor _ "" = ""
rotor a (x:xs)
    | a < 0 || a >= length (x:xs) = error "invalid offset number"
    | a == 0                  = (x:xs)
    | otherwise               = rotor (a-1) (xs++[x])

makeKey :: Int -> [(Char, Char)]
makeKey a = zip ['A'..'Z'] (rotor a ['A'..'Z'])

lookUp :: Char -> [(Char, Char)] -> Char
lookUp c [] = c
lookUp c ((x, y):rest)
    | c == x    = y
    | otherwise = lookUp c rest

encipher :: Int -> Char -> Char
encipher a c = lookUp c (makeKey a)

normalise :: String -> String
normalise "" = ""
normalise (x:xs)
    | x == ' '            = normalise xs
    | x `elem` ['a'..'z'] = toUpper x : normalise xs
    | otherwise           = x : normalise xs

encipherStr :: Int -> String -> String
encipherStr _ "" = ""
encipherStr a xs = [encipher a x | x <- normalise xs]

bruteForce :: String -> [String]
bruteForce "" = []
bruteForce cipherText = [encipherStr (n `mod` 26) cipherText | n <- [0..25]]


elemNum :: Eq a => a -> [a] -> Integer
elemNum _ [] = 0
elemNum x (y:ys)
    | x == y    = 1 + elemNum x ys
    | otherwise = elemNum x ys

unique :: Eq a => [a] -> [a]
unique [] = []
unique (x:xs)
    | x `elem` xs = unique (filter (/=x) xs)
    | otherwise   = x : unique xs

prop_uniqueElemNum :: Eq a => a -> [a] -> Bool
prop_uniqueElemNum x xs = (x `elem` unique xs) == (elemNum x xs == 1)

