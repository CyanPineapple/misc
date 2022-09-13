-- why b -> a -> b
-- cuz f acc x is still acc

ffoldl :: (b -> a -> b) -> b -> [a] -> b

ffoldl _ acc [] = acc

ffoldl f acc (x: xs) = ffoldl f (f acc x) xs



ffoldr :: (b -> a -> b) -> b -> [a] -> b

ffoldr _ acc [] = acc
ffoldr f acc (x: xs) = f (ffoldr f acc xs) x


