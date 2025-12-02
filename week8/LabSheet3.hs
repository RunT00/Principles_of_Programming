mult :: [Int] -> Int
mult [] = 0
mult xs = foldr (*) 1 xs

posList :: [Int] -> [Int]
posList [] = []
posList xs = filter (>0) xs

trueList :: [Bool] -> Maybe Bool
trueList [] = Nothing
trueList xs = Just(foldr (&&) True xs)

evenList :: [Int] -> Maybe Bool
evenList [] = Nothing
evenList xs = Just(length (filter odd xs) == 0)

maxList :: Ord a => [a] -> Maybe a
maxList [] = Nothing
maxList (x:xs) = Just(foldr max x xs)

inRange :: Int -> Int -> [Int] -> [Int]
inRange _ _ [] = []
inRange a b xs = filter (<=b) (filter (>=a) xs)

countPositives :: [Int] -> Int
countPositives [] = 0
countPositives xs = sum([1 | x <- filter (>0) xs])

-- foldr :: (a -> b -> b) -> b -> [a] -> b
myLength :: Ord a => [a] -> Int
myLength xs = foldr (+) 0 (map (const 1) xs)

myMap :: (a -> b) -> [a] -> [b]
myMap func xs = foldr (\x acc -> (func x) : acc) [] xs

myLength' :: Ord a => [a] -> Int
myLength' xs = foldr (\_ acc -> acc + 1) 0 xs