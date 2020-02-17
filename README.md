# BARNES HUT TREE BUILDER

### Aim
The aim of this project is to attempt to implement a module that can be used to build a quadtree from a list of bodies to be used in calculating their gravitational pull on each other, as per the barnes-hut algorithm.


N.B. This project is still in early development. The first stable build will be 1.0.0

### Install
```
npm i --save barnes-hut-tree-builder
```

### Usage
```jsx
import { BarnesHutTreeBuilder } from 'barnes-hut-tree-builder;

(async function() { 
    const treeBuilder = await BarnesHutTreeBuilder.create();
    
    const bodies = [
        {mass: 100, positionX: 50, positionY: 90},
        {mass: 100.01, positionX: 98, positionY: 91},
        {mass: 200, positionX: 309.45, positionY: 239.01111}
    ]
    
    return treeBuilder.build(bodies, 1000, 0, 0)
})()

```

Use the async method BarnesHutTreeBuilder.create to get a new BarnesHutTreeBuilder object.


The BarnesHutTreeBuilder has two methods: #build and buildToArray
They both accept an array of bodies, width and cornerX, cornerY (on the assumption that the area is a square)


Bodies should have the properties; mass, positionX and positionY.


#build returns an object tree where each node has up to four subnodes.
#buildToArray returns a two dimensional array, each item containing 12 values.
