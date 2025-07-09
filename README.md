# miniVim

**WHAT THE VERY EARLY VERSION LOOKS LIKE AS OF NOW**
![Screenshot from 2025-07-09 12-55-56](https://github.com/user-attachments/assets/401b542c-153e-428f-a080-a680f8654be2)



**miniVim** is a minimalist reimplementation of the classic Vim editor — built from scratch using C++ and Qt. The goal is not to recreate Vim in its entirety, but to explore how editors like Vim work under the hood, with fewer features and shortcuts for clarity and learning.

> 🚧 **Work In Progress**  
> This is a learning-focused project. Expect bugs, missing features, and experimental code.


## ⚙️ Prerequisites

To build and run miniVim on Ubuntu or Debian-based systems:

```bash
sudo apt update
sudo apt install -y qtcreator qtbase5-dev qt5-qmake cmake
```

---

## 🛠️ Building miniVim

Clone the repository:

```bash
git clone https://github.com/D0ge42/miniVim
cd miniVim
bash build.sh
```

After the build completes, run the editor with:

```bash
./miniVim
```

---

## 🔍 Project Structure

```
miniVim/
├── srcs/            # Source code files
├── includes/        # Header files
├── build/          # Out-of-source build directory
├── CMakeLists.txt  # Build configuration
└── README.md       # This file
```

---

## 🧠 Final Notes

miniVim is not trying to be a usable alternative to Vim.  
It's built purely for exploration, education, and fun.

If you're curious about how editors work or want to experiment with modal input and text buffer logic using C++ and Qt, you're in the right place.
