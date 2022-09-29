applyMaybe :: Maybe a -> (a -> Maybe b) -> Maybe b

applyMaybe Nothing _ = Nothing
applyMaybe (Just a) f = f a
