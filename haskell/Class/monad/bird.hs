--applyMaybe :: Maybe a -> (a -> Maybe b) -> Maybe b
--applyMaybe Nothing _ = Nothing
--applyMaybe (Just a) f = f a


--  return (0,0) >>= landLeft 3 >>= landRight 5



type Birds = Int
type Pole = (Birds, Birds)


landLeft :: Birds -> Pole -> Maybe Pole  
landLeft n (left,right)  
    | abs ((left + n) - right) < 4 = Just (left + n, right)  
    | otherwise                    = Nothing  
  
landRight :: Birds -> Pole -> Maybe Pole  
landRight n (left,right)  
    | abs (left - (right + n)) < 4 = Just (left, right + n)  
    | otherwise                    = Nothing
