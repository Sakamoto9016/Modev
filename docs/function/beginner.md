# Functions
## 1. Getting started
To make an application for Modev, it's easy. All you need to do was getting the latest release of Modev, run the emulator and start programming!
### Here's how
*(this section here is undocumented due to Modev hasn't been released.)*
### How to start programming?
First of all, you need to understand Lua since Modev was built to understand Lua 5.4.8.

For more infomation about Lua 5.4.x, please visit https://www.lua.org/manual/5.4/.

To start, create a file named `boot.lua`. Open the file and you will need to structure it like this:
```lua
f.manifest={}
--outside
function BOOT()
	--inside
end
```
#### What's required?
In `boot.lua`, there 2 things are required: The manifest and the loop definition.

`f.manifest` is where you will define your project. You can learn more about it [here](manifest.md).

`function BOOT() end` is your project loop. This is where your project will run in repeat. Everything outside it are one time codes, which is perfect for initalizations.

---
Click [here](#functions) to be taken to the top of the page.
<br><small>d21/m08/y2026 - Andrew Dexembre</small>

<!--
<br><small>d21/m08/y2026 - Andrew Dexembre</small>
-->