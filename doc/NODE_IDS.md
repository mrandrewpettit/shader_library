### NodeID
Renderman for Maya requires any shader to have a unique `rfm_nodeid` in its metadata. By default Maya has set aside 
nodeids 0 - 0x7ffff for local use.

These ids will normally suffice, but bugs would appear if on the off chance someone installs APOSL and is already using 
nodeids 0 - 0x7ffff. To be safe, I have registered a node ID block with maya, and APOSL uses nodeids 
0x0013cb80 - 0x0013cbff. 

- Visit [Autodesk Website](https://mayaid.autodesk.io/) for more clarification on node IDs

Below is a breakdown of each APOSL node and its nodeid.

| Node                  | ID            |
| --------------------- |:-------------:|
| apColor               | 0x0013cb80    |
| apColorConstruct      | 0x0013cb81    |
| apColorManipulate     | 0x0013cb82    |
| apColorMix            | 0x0013cb83    |
| apFloat               | 0x0013cb84    |
| apFloatAdd            | 0x0013cb85    |
| apFloatClamp          | 0x0013cb86    |
| apFloatDivide         | 0x0013cb87    |
| apFloatLayer          | 0x0013cb88    |
| apFloatMax            | 0x0013cb89    |
| apFloatMin            | 0x0013cb8a    |
| apFloatMix            | 0x0013cb8b    |
| apFloatMultiply       | 0x0013cb8c    |
| apFloatPower          | 0x0013cb8d    |
| apFloatRemap          | 0x0013cb8e    |
| apFloatSubtract       | 0x0013cb8f    |
| apFloatTrigonometry   | 0x0013cb90    |
| apManifoldConstruct   | 0x0013cb91    |
| apManifoldTransform   | 0x0013cb92    |
| apVectorLength        | 0x0013cb93    |
| apLobeSpecular        | 0x0013cb94    |
| apManifold2D          | 0x0013cb95    |
| apPrimvar             | 0x0013cb96    |
| apTexture             | 0x0013cb97    |
| apFloatStep           | 0x0013cb98    |
|                       | 0x0013cb99    |
|                       | 0x0013cb9a    |
|                       | 0x0013cb9b    |
|                       | 0x0013cb9c    |
|                       | 0x0013cb9d    |
|                       | 0x0013cb9e    |
|                       | 0x0013cb9f    |
|                       | 0x0013cba0    |
|                       | 0x0013cba1    |
|                       | 0x0013cba2    |
|                       | 0x0013cba3    |
|                       | 0x0013cba4    |
|                       | 0x0013cba5    |
|                       | 0x0013cba6    |
|                       | 0x0013cba7    |
|                       | 0x0013cba8    |
|                       | 0x0013cba9    |
|                       | 0x0013cbaa    |
|                       | 0x0013cbab    |
|                       | 0x0013cbac    |
|                       | 0x0013cbad    |
|                       | 0x0013cbae    |
|                       | 0x0013cbaf    |
|                       | 0x0013cbb0    |
|                       | 0x0013cbb1    |
|                       | 0x0013cbb2    |
|                       | 0x0013cbb3    |
|                       | 0x0013cbb4    |
|                       | 0x0013cbb5    |
|                       | 0x0013cbb6    |
|                       | 0x0013cbb7    |
|                       | 0x0013cbb8    |
|                       | 0x0013cbb9    |
|                       | 0x0013cbba    |
|                       | 0x0013cbbb    |
|                       | 0x0013cbbc    |
|                       | 0x0013cbbd    |
|                       | 0x0013cbbe    |
|                       | 0x0013cbbf    |
|                       | 0x0013cbc0    |
|                       | 0x0013cbc1    |
|                       | 0x0013cbc2    |
|                       | 0x0013cbc3    |
|                       | 0x0013cbc4    |
|                       | 0x0013cbc5    |
|                       | 0x0013cbc6    |
|                       | 0x0013cbc7    |
|                       | 0x0013cbc8    |
|                       | 0x0013cbc9    |
|                       | 0x0013cbca    |
|                       | 0x0013cbcb    |
|                       | 0x0013cbcc    |
|                       | 0x0013cbcd    |
|                       | 0x0013cbce    |
|                       | 0x0013cbcf    |
|                       | 0x0013cbd0    |
|                       | 0x0013cbd1    |
|                       | 0x0013cbd2    |
|                       | 0x0013cbd3    |
|                       | 0x0013cbd4    |
|                       | 0x0013cbd5    |
|                       | 0x0013cbd6    |
|                       | 0x0013cbd7    |
|                       | 0x0013cbd8    |
|                       | 0x0013cbd9    |
|                       | 0x0013cbda    |
|                       | 0x0013cbdb    |
|                       | 0x0013cbdc    |
|                       | 0x0013cbdd    |
|                       | 0x0013cbde    |
|                       | 0x0013cbdf    |
|                       | 0x0013cbe0    |
|                       | 0x0013cbe1    |
|                       | 0x0013cbe2    |
|                       | 0x0013cbe3    |
|                       | 0x0013cbe4    |
|                       | 0x0013cbe5    |
|                       | 0x0013cbe6    |
|                       | 0x0013cbe7    |
|                       | 0x0013cbe8    |
|                       | 0x0013cbe9    |
|                       | 0x0013cbea    |
|                       | 0x0013cbeb    |
|                       | 0x0013cbec    |
|                       | 0x0013cbed    |
|                       | 0x0013cbee    |
|                       | 0x0013cbef    |
|                       | 0x0013cbf0    |
|                       | 0x0013cbf1    |
|                       | 0x0013cbf2    |
|                       | 0x0013cbf3    |
|                       | 0x0013cbf4    |
|                       | 0x0013cbf5    |
|                       | 0x0013cbf6    |
|                       | 0x0013cbf7    |
|                       | 0x0013cbf8    |
|                       | 0x0013cbf9    |
|                       | 0x0013cbfa    |
|                       | 0x0013cbfb    |
|                       | 0x0013cbfc    |
|                       | 0x0013cbfd    |
|                       | 0x0013cbfe    |
|                       | 0x0013cbff    |
