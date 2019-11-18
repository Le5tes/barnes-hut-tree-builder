import * as tree from '../build/build.js'

export class BarnesHutTreeBuilder {
    constructor(module) {
        if (module){
            this.module = module;
            this.treeBuilder = module.getTreeBuilder();
        } 
    }
    
    static async create() {
        const module = await tree.ready;
        return new BarnesHutTreeBuilder(module);
    }
    
    buildToArray(arr) {
        let result;

        result = this.treeBuilder.build(this.convertToBuffer(arr), arr.length);

        return this.convertToNodeArray(result);
    }

    convertToBuffer(bodies) {
        const typedArray = new Float64Array(bodies.length * 3)

        for (let i=0; i<bodies.length; i++) {
            typedArray[i * 3] = bodies[i].mass;
            typedArray[i * 3 + 1] = bodies[i].posX;
            typedArray[i * 3 + 2] = bodies[i].posY;
        }

        const buffer = this.module._malloc(typedArray.length * typedArray.BYTES_PER_ELEMENT)

        this.module.HEAPF64.set(typedArray, buffer >> 3)

        return buffer
    }

    convertToNodeArray(buffer) {
        const nodeArray = []
        const node = Array(10).fill('').map((val, i) => {
           return this.module.HEAPF64[buffer/Float64Array.BYTES_PER_ELEMENT + i];
        })
        nodeArray.push(node)

        return nodeArray;
    }
}
