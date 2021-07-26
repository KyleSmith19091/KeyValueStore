<!-- Heading -->
<div align="center">
    <h1>Transactional Key Value Store Implmentation</h1>
</div>

<p>
This is an <strong>in progress implmentation</strong> of a transactional Key-Value store implementation from scratch. Currently we only use few standard library functions such as strings, io and unordered maps as the stores. This is purely educational, where I wanted to implement as much of the functionality from scratch, such as creating my own Stack and in the future a hashmap implementation.
</p>

---
## Installation ⚡️

* Building from sratch

This is requires a g++ compiler, that is also able to compile c++ 11
```bash
make
```
<p>
This creates the executable in the build directory
</p>

You'll then be presented with the following prompt
```bash
> 
```

This 'mini-shell' environment will serve as you interface into the key-value store

## CRUD Operations ⭐️
<strong>** Note, keys are case sensitive, but the operations are not</strong>

<h4 align="center">READ</h4>

```bash
> GET KEY
```
<h4 align="center">WRITE</h4>

```bash
> SET KEY VALUE
```

<strong>** In this case the value can be anything, the interpreter will assume that all input after the given KEY is the value.</strong>

<strong>** Space seperated data will include the spaces in the store. </strong>

<h4 align="center">UPDATE</h4>

```bash
> PUT KEY VALUE
```

** SET can also be used as a PUT, it will overwrite the key's value

<h4 align="center">DELETE</h4>

```bash
> DELETE KEY
```

## Other Operations 🧪

<h4 align="center">EXIT</h4>
To gracefully exit the shell, CTRL+C or your equivalent will also work

```bash
> EXIT
```

<h4 align="center">PRINT</h4>
To Print the current active transaction's store

```bash
> PRINT
```

## Additional Notes 🎉
You can customise the prompt token, by changing the constructor value in the Main.cpp file

```c++
int main() {
	// Interface into key-value store
	Shell s("❯");
	s.init();

	return 0;
}
```
