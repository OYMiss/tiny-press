# tiny-press

A tiny static blog generator. 

[Example](https://oymiss.github.io) powered by Github Pages.


## Install

macOS:

```
brew tap OYMiss/taps
brew install tiny-press
```

Linux:

```bash
git clone git@github.com:OYMiss/tiny-press.git
cd tiny-press
git clone git@github.com:OYMiss/marktool.git
cmake -B build && cd build && make
```

## Usage

To preview using Nginx:

```
tiny_press -i /Users/oymiss/Developer/blog-doc -o /usr/local/var/www
```
