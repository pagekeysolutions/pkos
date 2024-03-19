# OS14: Organizing Our OS

[YouTube Video](https://youtu.be/Qa-WjNWkNeA)

In this video, we reorganize the entire project, taking it from cluttered to modular in less than 10 minutes.

## Timestamps

- 0:00 Intro, Overview
- 0:25 Running the OS
- 0:43 The Main Changes
- 1:16 Other Minor Changes
- 1:34 Lessons Learned
- 2:40 The (New!) File Tree
- 3:42 Code Diff Walkthrough
- 7:06 Outro

## References

- [Recursive Make Considered Harmful paper](https://accu.org/journals/overload/14/71/miller_2004/)
    - Goes into detail about why you shouldn't use separate `Makefile`s for each submodule in your project
- [GNU Make Include docs](https://www.gnu.org/software/make/manual/html_node/Include.html)
    - Tell you how to use `include` in GNU Make, which we use in this video

## Other Resources

- [Implementing Non-Recursive Make](http://sites.e-advies.nl/nonrecursive-make.html)
    - A helpful article
- [boilermake](https://github.com/dmoulding/boilermake)
    - Seems to be a boilerplate for Make projects using `include`
    - Definitely too complicated for me to understand/use, but a helpful reference

## Code

- [Link to tag](https://github.com/pagekeysolutions/pkos/releases/tag/vid%2Fos014)
- [Diff from previous video](https://github.com/pagekeysolutions/pkos/compare/vid/os013..vid/os014)
