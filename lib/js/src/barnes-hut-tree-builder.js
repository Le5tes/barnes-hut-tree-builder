import * as tree from '../build/build.js'

export class BarnesHutTreeBuilder {
    constructor(getTreeBuilder) {
        if (getTreeBuilder) this.treeBuilder = getTreeBuilder();
    }
    
    static async create() {
        const module = await tree.ready;
        return new BarnesHutTreeBuilder(module.getTreeBuilder);
        // return new BarnesHutTreeBuilder(() => new module.TreeBuilder());
    }
}
