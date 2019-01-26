library(tidyverse)
library(babynames)
data(babynames)

Rcpp::sourceCpp('grams.cpp')

fnames <- babynames %>%
  filter(year %in% 1940:2000) %>%
  group_by(name) %>%
  summarise(wt = sum(prop)) %>%
  sample_n(10, weight = wt) %>%
  mutate_all(toupper) %>%
  select(name_a = name) %>%
  mutate(name_b = name_a)

name_pairs <- cross_df(fnames)

k <- grams(fnames$name_a)
