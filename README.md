# tiny-press

A tiny static blog generator. 

[Example](https://oymiss.github.io) powered by Github Pages.

```bash
git clone git@github.com:OYMiss/tiny-press.git
cd tiny-press
git clone git@github.com:OYMiss/marktool.git
cmake -B build && cd build && make
# generate blog files in `/Users/oymiss/Developer/blog-doc` to the default www location of nginx.
./tiny_press -i /Users/oymiss/Developer/blog-doc -o /usr/local/var/www
```
