# Architecture

## Overview

Nixreg is structured around three core abstractions: `NixieDigitMap`, `NixieFloat`, and `ShadowRegister`. End users interact only with these — internal implementation details such as `BitBuffer` are created via factory methods during initialisation and are not part of the public API.

## Core Types

### `NixieDigitMap`
Describes the mapping between a single nixie tube's cathodes and the physical output pins of the shift register. Supports two construction modes:

**Contiguous** — pins are sequential from a start pin:
```cpp
NixieDigitMap digit0 = NixieDigitMap::contiguous(0);
NixieDigitMap digit0 = NixieDigitMap::contiguous(0, .decimal = 10);
```

**Scattered** — pins are explicitly mapped per cathode (index = digit value):
```cpp
NixieDigitMap digit1 = NixieDigitMap::scattered({4,7,2,15,8,1,22,11,6,19});
NixieDigitMap digit1 = NixieDigitMap::scattered({4,7,2,15,8,1,22,11,6,19}, .decimal = 20);
```

Both modes produce an identical `NixieDigitMap` internally. Downstream types do not need to know which construction method was used.

Decimal pin is optional. Omitting it indicates the tube has no decimal (or it is unused).

### `NixieFloat<N>`
Represents N nixie tubes as a single logical display. Accepts N `NixieDigitMap`s and exposes a `set()` method for writing a value. Encodes the value into the appropriate bits based on the digit maps it was constructed with.

```cpp
NixieFloat<3> display_a = { digit0, digit1, digit2 };
display_a.set(3.14);
```

Updating a `NixieFloat` propagates the change to the parent `ShadowRegister` immediately. If atomic multi-float updates are needed, use `ShadowRegister::begin_batch()` / `end_batch()` to defer flushing until both are written.

### `ShadowRegister`
Owns the full bitset representing all shift register outputs. Width is explicitly declared at construction time since it reflects the physical wiring (number and types of chained registers) rather then any single chip's properties.
Owns the SPI handle and flushes automatically on any write. Constructed via factory method:

```cpp
ShadowRegister reg = ShadowRegister::create(64, display_a, display_b);
```

Flushing shifts the full bitset out over SPI/shift clock to the physical register(s).

## Internal Types

### `BitBuffer` (internal)
A positional view into the `ShadowRegister`'s bitset. Created by the `ShadowRegister` factory and handed to each `NixieFloat` so it knows which bit range to write into. Not exposed in the public API.

## Batched Updates

To prevent visible flicker when updating multiple `NixieFloat`s in the same frame:

```cpp
reg.begin_batch();
display_a.set(1.23);
display_b.set(4.56);
reg.end_batch(); // single flush here
```

## Extending to Other Shift Registers

`ShadowRegister` is designed to be generic. To support a new shift register, define its pin width and SPI parameters — the rest of the abstraction is device-agnostic.
