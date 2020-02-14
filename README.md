# SFML Toolkit

A collections of systems that will make your life easier when using SFML.

## Currently Available

- (Header only) Control events's propagation through your objects: [EventListener](https://github.com/Hazurl/SFML-Toolkit/blob/master/doc/Events/EventListener.md)
- (Header only) Auto loading/unloading ressources : [Ressource](https://github.com/Hazurl/SFML-Toolkit/blob/master/doc/Ressource/Ressource.md)
- Generate text with multiple styles : [FancyText](https://github.com/Hazurl/SFML-Toolkit/blob/master/doc/FancyText/FancyText.md)
- (Header only) Animate easily : [Animated](https://github.com/Hazurl/SFML-Toolkit/blob/master/doc/Animated/Animated.md)
- (Header only) Draw easily : [Gizmo](https://github.com/Hazurl/SFML-Toolkit/blob/master/doc/Gizmo/Gizmo.md)
- (Header only) Quality of life : [QoL](https://github.com/Hazurl/SFML-Toolkit/blob/master/doc/QoL/QoL.md)
- Restrict draw area : [Clipper](https://github.com/Hazurl/SFML-Toolkit/blob/master/doc/Clipper/Clipper.md)
- 9-slice scaling : [NineSlice](https://github.com/Hazurl/SFML-Toolkit/blob/master/doc/NineSlice/NineSlice.md)

## Usage

You can build each part separately:
- `make X-shared` to build a shared library of the module X
- `make X-static` to build a static library of the module X
- `make X` to build the example of the module X
- `make run-X` to build the example of the module X and run it

You can replace `X` by:
- `eventlistener`
- `ressource`
- `fancytext`
- `animated`
- `gizmo`
- `qol`
- `clipper`
- `nineslice`

> Animated, QoL, Gizmo, Event Listener and Ressource are header-only library
