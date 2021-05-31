# ACLIB Injector module

Standalone injector module for [ACLIB](https://github.com/ACLIB/ACLIB).
Injects a dll into an executable from python.

> Work in progress.

Follow the [Documentation](https://github.com/ACLIB/Documentation) for more details.

# Example

```python
import aclib_injector as injector

inject = injector.DLLInject('your executable.exe', 'path_to_your_dll/your_dll.dll', 1000)
print(inject.process, inject.dll, inject.interval)
injector.run() # Blocks until process is found and DLL is injected.
```
