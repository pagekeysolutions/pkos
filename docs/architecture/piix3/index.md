---
status: proposed
creation-date: "2024-02-27"
authors: [ "@stephengrice" ]
coach: "n/a"
approvers: [ "@jonstrong", "@tonyprogrammer" ]
---

# PIIX3 Hard Drive Driver

## Summary

In order to store persistent data, we need a hard drive driver. The QEMU i386 system contains a PIIX3 hard drive, so we'll start by writing some code to interface with it directly. Once this driver is available, we can use it for higher level abstractions such as filesystems. Also, we can use what we learn from this to add support for other hard drive models.

## Motivation

We need to store persistent data or else this is really boring and useless.

### Goals

- Be able to write a string to the QEMU-provided hard drive
- Be able to read the string back from the hard drive (even after shutdown if same drive is attached)

### Non-Goals

Out of scope:

- Filesystem development
- Any other device except for the PIIX3

## Proposal

<!--
This is where we get down to the specifics of what the proposal actually is,
but keep it simple!  This should have enough detail that reviewers can
understand exactly what you're proposing, but should not include things like
API designs or implementation. The "Design Details" section below is for the
real nitty-gritty.

You might want to consider including the pros and cons of the proposed solution so that they can be
compared with the pros and cons of alternatives.
-->

## Design and implementation details

<!--
This section should contain enough information that the specifics of your
change are understandable. This may include API specs (though not always
required) or even code snippets. If there's any ambiguity about HOW your
proposal will be implemented, this is the place to discuss them.

If you are not sure how many implementation details you should include in the
blueprint, the rule of thumb here is to provide enough context for people to
understand the proposal. As you move forward with the implementation, you may
need to add more implementation details to the blueprint, as those may become
an important context for important technical decisions made along the way. A
blueprint is also a register of such technical decisions. If a technical
decision requires additional context before it can be made, you probably should
document this context in a blueprint. If it is a small technical decision that
can be made in a merge request by an author and a maintainer, you probably do
not need to document it here. The impact a technical decision will have is
another helpful information - if a technical decision is very impactful,
documenting it, along with associated implementation details, is advisable.

If it's helpful to include workflow diagrams or any other related images.
Diagrams authored in GitLab flavored markdown are preferred. In cases where
that is not feasible, images should be placed under `images/` in the same
directory as the `index.md` for the proposal.
-->

## Alternative Solutions

<!--
It might be a good idea to include a list of alternative solutions or paths considered, although it is not required. Include pros and cons for
each alternative solution/path.

"Do nothing" and its pros and cons could be included in the list too.
-->
