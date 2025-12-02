doubleMe x = x + x
doubleUs x y = doubleMe x + doubleMe y
doubleSmallNum x = if x > 100 then x else x * 2
swap (x, y) = (y, x)

length' xs = sum[1 | _ <- xs]
keepLowerCase st = [c | c <- st, c `elem` ['a'..'z']]

xxs = [[1,3,5,7,8,7,6,2], [2,3,4,5,6,1], [12,6,7,8,9,4,6,77]]

add::(Int, Int) -> Int
add(x, y) = x + y

zeroto:: Int -> [Int]
zeroto n = [0..n]

add':: Int -> (Int -> Int)
add' x y = x + y

mult:: Int -> (Int -> (Int -> Int))
mult x y z = x * y * z
