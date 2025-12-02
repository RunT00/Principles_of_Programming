-- elemNum :: Eq a => a -> [a] -> Integer
-- elemNum _ [] = 0
-- elemNum x (y:ys)
--     | x == y    = 1 + elemNum x ys
--     | otherwise = elemNum x ys

-- elemNum x xs = sum([1 | y <- filter (==x) xs])

elemNum :: Eq a => a -> [a] -> Integer
elemNum x xs| null xs = 0
            | x == (head xs) = 1 + (elemNum x (tail xs))
            | otherwise = elemNum x (tail xs)

unique :: Eq a => [a] -> [a]
unique xs = [x | x <- xs, elemNum x xs == 1]

prop_elemNum_unique :: Eq a => a -> [a] -> Bool
prop_elemNum_unique x ys = (elemNum x ys == 1) || not (x `elem` unique ys)

insert :: Ord a => a -> [a] -> [a]
insert x [] = [x]
insert x (y:ys) | x < y = x:y:ys
                | otherwise = y : insert x ys

isort :: Ord a => [a] -> [a]
isort [] = []
isort (x:xs) = insert x (isort xs)