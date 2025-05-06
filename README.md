ElPsyFS
=======
![cover](https://raw.githubusercontent.com/mmdbalkhi/ElpsyFS/refs/heads/main/docs/_static/cover.png)

> A tiny educational filesystem in C — because the future is not written on ext4.

A minimalist educational filesystem written in C — inspired by the internals of real-world filesystems.  
Named after *El Psy Kongroo* from Steins;Gate. For those who seek to understand the low-level truth of storage.

## Build & Run

Requires: `meson`, `ninja`, `gcc`

```bash
meson setup build
ninja -C build
./build/fs_create disk.img
./build/fs_format disk.img
./build/fs_check disk.img
```

## License

MIT – Use it, break it, learn from it.
