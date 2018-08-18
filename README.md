# SFML Toolkit

A collections of systems that will make your life easier when using SFML.

## Currently Available

- Control events's propagation through your objects: [EventListener](https://github.com/Hazurl/SFML-Toolkit/blob/master/doc/Events/EventListener.md)
- Auto loading/unloading ressources : [Ressource](https://github.com/Hazurl/SFML-Toolkit/blob/master/doc/Ressource/Ressource.md)

## Usage

You can build each part separately:
- `make X-shared` to build a shared library of the module X
- `make X-static` to build a static library of the module X
- `make X` to build the example of the module X
- `make run-X` to build the example of the module X and run it

You can replace `X` by:
- `eventlistener`
- `ressource`
