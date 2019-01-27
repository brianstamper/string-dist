library(tidyverse)
library(babynames)
data(babynames)

Rcpp::sourceCpp('cross_join.cpp')
Rcpp::sourceCpp('grams.cpp')

### Simulate an initial set
fnames <- babynames %>%
  filter(year %in% 1940:2000) %>%
  group_by(name) %>%
  summarise(wt = sum(prop)) %>%
  sample_n(1000, weight = wt) %>%
  mutate_all(toupper)

names_list <- fnames$name

name_pairs <- cross_join(fnames$name, fnames$name)
name_pairs <- mutate(name_pairs, score = grams(name_pairs))


### Simulate an additional set
fnames <- babynames %>%
  filter(year %in% 1940:2000) %>%
  group_by(name) %>%
  summarise(wt = sum(prop)) %>%
  sample_n(2000, weight = wt) %>%
  mutate_all(toupper)

new_names <- setdiff(fnames$name, names_list) 

new_name_pairs <- cross_join(new_names, c(names_list, new_names))
new_name_pairs <- mutate(new_name_pairs, score = grams(new_name_pairs))

names_list <- c(new_names, names_list)
name_pairs <- bind_rows(name_pairs, new_name_pairs)

# treat as undirected to reduce storage
backward <- name_pairs %>%
  filter(a > b)

name_pairs <- name_pairs %>%
  filter(a <= b)

# make sure the ones that were backward are in fact stored forward
name_pairs <- name_pairs %>%
  bind_rows(backward %>%
              rename(b = a, a = b) %>%
              anti_join(name_pairs, by = c('a', 'b')))

