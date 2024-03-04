# pkos - PageKey Operating System

Welcome to PKOS! This is an operating system written completely from scratch, working its way up from assembly to higher level languages like C. This was created for educational purposes and documented in the OS Series from PageKey Tech

Please see the docs site at [docs.pkos.pagekey.io](https://docs.pkos.pagekey.io).

## Video Series

This package has been developed on video on the PageKey Tech YouTube channel. You can check the series out [here](https://www.youtube.com/playlist?list=PL3Kz_hCNpKSTFCTJtP4-9mkYDVM7rAprW).

## Discord

[Join the Discord](https://discord.gg/5m5yFgDPF5) to discuss this project and connect with others!

## Docs

See the [docs folder](docs/) for all of the messy notes used to make these videos. You can open it as an Obsidian vault for a nicer experience. It'll also allow you to view the `.canvas` files properly.

## Getting Started

Try these commands to get started in a hurry.

1. Ensure you have `docker` and `docker-compose` installed and ready to go on your system.

2. Run `./scripts/docker_shell` to build the dev environment and get a shell inside of it to work in.

3. From inside the system, run the OS with: `./scripts/os.py run`.

## Commands

Run `./scripts/os.py` with no arguments to list the usage. It includes subcommands for building, testing, and running the OS.

## Troubleshooting

- If you're getting errors initializing the display when using Docker:
  - Try the following if you're on Mac or Linux: `xhost local:root`
  - If you're on Windows, make sure that you have an X11 server installed and running.
    - Try [xming](https://sourceforge.net/projects/xming/) or [VcXsrv](https://sourceforge.net/projects/vcxsrv/)

## How to Debug and Set Breakpoints

1. Run `./scripts/docker_shell` to get into the container.

2. Run `./scripts/os.py run_debug` to start in debug mode.

3. In the GDB prompt in your terminal, type `whatever.c:1` to break when line 1 of `whatever.c` is executed.

## How to Create Bootable USB on Linux

1. Run `./scripts/docker_shell` to get into the container.

2. Run `./scripts/os.py build` build the OS.

3. Exit the container: `exit`

4. Plug in a USB drive that you don't mind erasing. Run `dmesg -w` before plugging it in to watch and see which device name it is assigned.

5. Run the following command (replace `/dev/sdx` with the USB device path):

```bash
dd if=dist/pkos.iso of=/dev/sdx
```

## About This Repository 

This repository will hold all versions of PKOS, from the simplest to the latest. To follow along with the tutorial, each increment of the OS will be accessible to you as a "release" on GitHub. You just have to clone this repository and checkout the right tag for the video you watched. Then, you should be able to build the code and run it on your own system.

## Running the Code

Use the "Release Tag" listed below for the video you would like to run the code for. Replace `TAG` with the actual Release Tag in what's below:

```bash
git clone https://gitlab.com/pagekeytech/pkos
cd pkos
git checkout (whichever tag)
make
make run
```

## Resources

Aside from a ton of StackOverflow answers, the following were super helpful in pulling together the information for these lessons:

* [os-dev PDF from University of Birmingham (Nick Blundell)](https://www.cs.bham.ac.uk/~exr/lectures/opsys/10_11/lectures/os-dev.pdf)
* [os-tutorial by cfenollosa on GitHub](https://github.com/cfenollosa/os-tutorial)
* [Ralph Brown's BIOS Interrupt List (Download)](http://www.cs.cmu.edu/~ralf/files.html)

More sources are availble on the writeup for each post in [the series](https://pagekeytech.com/projects/pkos).

## Building the Docker Image

The Docker image is built manually and pushed to GitLab. The following steps are used to do that:

```bash
docker login registry.gitlab.com
docker-compose build
docker-compose push
```

## Running Tests

- Integration tests:
  - `pip install -r requirements.txt`
  - `pytest`
- Unit tests:
  - `./scripts/test_unit`
  - Use `NOCOV=1 ./scripts/test_unit` to skip coverage

## Articles and Videos

See https://pagekey.io/projects/pkos for a full list of blog posts and videos showing the development of this project from day one.
