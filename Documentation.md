# Development Design Notes

This is to keep notes on the thought process of the solution.

Analysis of the reference command
---------------------------------

```
(tr "[:space:][:punct:]" "\n" | sort | grep -v "^$" | uniq -c | sort -nr | head -40) < moby.txt

tr "[:space:][:punct:]" "\n"    // Step 1: truncate and convert all space and punct to linefeed \n
sort                            // Step 2: sort them
grep -v "^$"                    // Step 3: Take only non-empty lines
uniq -c                         // Step 4: Filter matching lines and count them, output in "count" "string" format
sort -nr                        // Step 5: Sort by count numberic value and reserve (highest count first)
head -20                        // Step 6: Limit the output to 20
```

Based on the reference output, these additional requirements need to be meet:
- words are counted case sensitive, i.e. To != to
- non-letter need to be taken care of (!,.[]) etc. This is what the tr [:punct:] does.
- ' is also non-letter that break words - e.g. Gutenberg's -> ["Gutenberg", "s"]
- Numbers are considered a word or part of a word, e.g. 16th
- In the final output, words that has same freq are ordered in
   ```
   1 voyaging
   1 voyagers
   1 VOYAGER
   1 voyaged
   ```
   i.e. they are cap insensitive and always check the next letter if current letter is the same

Design Choice Note
------------------
- Mostly header only for simplicity
- The spec stated only 2 copy of the result can be hold on ram.

  For the purpose of this project, my understanding is one for table(word -> count), another for table(count -> word)
- The initial version use map and multimap for the result - it does the job if the order of the words with same count in final display is not an issue.
- For the final solution,
  - unordered_map is used for table(word -> count):

    Only counting unique words and order is not important, so using unordered_map is faster
  - multiset for the table(count -> word):

    The entries need to be ordered by both K and V in a specific way to matching the reference output, so use multiset. (It does seem like set can also be used as there shouldn't be a pair in the map that's equal in both K and V).

    multiset is slightly(negligible) better as it does not do equal heck.

Build Infrastructure Note
-------------------------
- About cmake project files

  cmake is used as a portable way to generate the necessary makefiles.
  For this exercise, only tested the build under Ubuntu with make.

- About googletest dependency

  For the purpose of this exercise, the googletest external dependency is pulled from github repo at build time.
  Ideally a stable release should be kept and downloaded from internal network.   

- About auto code formatting

  .clang-format contains the formatting rule for clang-format.
  In VSCode, extension can be installed to automatically format on save.

- About git

  This project is a git repo.

- About CI

  The .travis.yml is added. The travis-ci.org can be used as a CI backend, when repo is make available in github.

- About Docker

  The Dockerfile is added as a bonus. It can be used to generate the docker image needed to build this project.
  It keeps the build environment isolated from the host environment and avoid potential conflict - especially
  if the build requires old tools.