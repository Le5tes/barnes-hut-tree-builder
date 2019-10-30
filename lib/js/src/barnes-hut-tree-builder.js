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

        result = this.treeBuilder.build(arr, arr.length)

        return result;
    }
}
