# OS14: Organizing Our OS Code

started:: 2022-02-12
uploaded:: 2022-04-09
published:: 2022-04-09

## Notes

**FOR THIS VIDEO: JUST REORG THE CODEBASE AND SHOW HOW IT'S DONE WITH HEADERS, ETC**

- A chain of ideas on how to structure Makefiles
	- https://www.oreilly.com/library/view/managing-projects-with/0596006101/ch06.html
	- https://accu.org/journals/overload/14/71/miller_2004/
	- https://stackoverflow.com/questions/19307258/how-to-include-a-makefile-into-an-other-makefile
	- https://github.com/dmoulding/boilermake/blob/master/Makefile
	- http://sites.e-advies.nl/nonrecursive-make.html

- https://www.gnu.org/software/make/manual/html_node/Include.html

### Video Notes
- Quick Overview (The Story)
	- Started trying to dive into adding some kind of VGA commands BUT realized it was almost impossible to edit kernel.c (turning into spaghetti code)
	- Split kernel.c into different source files and headers
	- Rewrite Makefile to be modular (but not recursive!)
	- Fix ISO build in Docker
- Lessons Learned
	- How to structure GNU Make Makefiles using include directive
	- How header files work - was always a mystery to me until now sadly


OS13 \<TBD> reorg
Monday, July 13, 2020
9:22 PM

<http://nuclear.mutantstargoat.com/articles/make/>
-   \$@ is the target
-   \$\^ contains the dependencies
-   Use % for wildcard of target and deps
<http://web.mit.edu/gnu/doc/html/make_4.html>
-   Targets : dependencies
    -   Command