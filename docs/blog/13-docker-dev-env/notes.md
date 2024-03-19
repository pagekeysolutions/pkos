# OS13: Docker Dev Environment

- [x] Fix tags
- [x] Move wiki info over
	- [x] Instructions in README
	- [x] Links to my website in README
	- [x] Links to tags / diffs in README
- [x] Write rough script using notes below
- [x] Record video
- [x] Edit video
- [x] Post video

- Add to README:
	- xhost local:root needed to get x windows working
	- MAke sure option to run with ISO is in there

## Rough Script
- Thanks to those who encouraged
	- And sorry it took so long
- Cleanup / restarting this project
	- Retagged everything
	- Deleted the wiki
	- Created docs area on site
		- Aside: Docusaurus rocks. Future video
- Docker dev env
	- Demo - just do `docker-compose up`
	- Alternative: get a shell with `bin/docker_run`
		- Really just `docker-compose run pkos_dev` under the hood
	- Other commands
		- Build
		- Shell
	- Devcontainers for VScode: I tried, but failed
	- Troubleshooting Docker x11 windows (Ubuntu, Mac)
		- `xhost local:root`
			- Safer than `xhost +` which turns off all access control