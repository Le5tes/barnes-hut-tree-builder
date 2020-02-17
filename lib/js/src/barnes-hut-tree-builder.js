import * as tree from '../core/build.js'
const window = window || null;
const performance = (window && window.performance) || require('perf_hooks').performance;

export class BarnesHutTreeBuilder {
    constructor(module, options = {}) {
        this.options = options;
        
        if (module){
            this.module = module;
            this.treeBuilder = module.getTreeBuilder();
        } 
    }
    
    static async create(options = {}) {
        const module = await tree.ready;
        return new BarnesHutTreeBuilder(module, options);
    }
    
    buildToArray(arr, width, cornerX, cornerY) {
        const startTime = performance.now();
    
        const buffer = this.convertToBuffer(arr);
        const startTimeCore = performance.now();
        const result = this.treeBuilder.build(buffer, arr.length, width, cornerX, cornerY);
        const endTimeCore = performance.now();
        const convertedResult = this.convertToNodeArray(result, this.treeBuilder.getTreeLength());

        const endTime = performance.now();
        if (this.options.debug) { console.log(`Time - total: ${endTime - startTime}ms, core: ${endTimeCore - startTimeCore}ms`) }
        return convertedResult;
    }
    
    build(bodies, width, cornerX, cornerY) {
        const nodes = this.buildToArray(bodies, width, cornerX, cornerY);
        
        return this.buildNodeObject(nodes[0], nodes, bodies);
    }
    
    buildNodeObject(node, nodes, bodies) {
        return {
            positionX: node[0],
            positionY: node[1],
            mass: node[2],
            width: node[3],
            cornerX: node[4],
            cornerY: node[5],
            body: bodies[node[7]],
            subnodes: [node[8], node[9], node[10], node[11]]
                .filter(val => val != -1)
                .map(val => this.buildNodeObject(nodes[val], nodes, bodies))
        }
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
        const nodeArray = new Array(length)
        for (let j = 0; j < length; j++) {
            const node = Array(12)
            
            for (let i = 0; i < 12; i++) {
                node[i] = this.module.HEAPF64[buffer/Float64Array.BYTES_PER_ELEMENT + i + j * 12]
            }
            
            if(node.some(elem => elem != 0)) {
                nodeArray[j] = node;
            } else { 
                nodeArray.length = j;
                j = length
            } 
        }
        return nodeArray;
    }
}
