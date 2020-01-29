import * as tree from '../core/build.js'

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
    
    buildToArray(arr, width, cornerX, cornerY) {
        let result;

        result = this.treeBuilder.build(this.convertToBuffer(arr), arr.length, width, cornerY, cornerY);

        return this.convertToNodeArray(result, this.treeBuilder.getTreeLength());
    }

    convertToBuffer(bodies) {
        const typedArray = new Float64Array(bodies.length * 3)

        for (let i=0; i<bodies.length; i++) {
            typedArray[i * 3] = bodies[i].positionX;
            typedArray[i * 3 + 1] = bodies[i].positionY;
            typedArray[i * 3 + 2] = bodies[i].mass;
        }

        const buffer = this.module._malloc(typedArray.length * typedArray.BYTES_PER_ELEMENT)

        this.module.HEAPF64.set(typedArray, buffer >> 3)

        return buffer
    }

    convertToNodeArray(buffer, length) {
        const nodeArray = []
        for (let j = 0; j < length * 10; j++) {
            const node = Array(12).fill('').map((val, i) => {
               return this.module.HEAPF64[buffer/Float64Array.BYTES_PER_ELEMENT + i + j * 12];
            })
            
            if(node.some(elem => elem != 0)) {
                nodeArray.push(node);
            } else { j = length * 10 } 
        }
        return nodeArray;
    }
}
