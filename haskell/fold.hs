-- why b -> a -> b
-- cuz f acc x is still acc

ffoldl :: (b -> a -> b) -> b -> [a] -> b

ffoldl _ acc [] = acc

ffoldl f acc (x: xs) = ffoldl f (f acc x) xs



ffoldr :: (b -> a -> b) -> b -> [a] -> b

ffoldr _ acc [] = acc
ffoldr f acc (x: xs) = f (ffoldr f acc xs) x

-- write ffoldr :: (a->b->b) -> b -> t a -> b
-- write the process out helps you write the def
-- e.g foldr (+) 0 [1, 2, 3, 4]
-- ==  foldr (+) 0 [1, 2, 3, 4]
-- ==  ...
-- ==  1 + (2 + (3 + (4 + (foldr (+) 0 []))))

ffoldr _ acc [] = acc

ffoldr f acc [x: xs] = 
	f xs (ffoldr f acc [xs])
