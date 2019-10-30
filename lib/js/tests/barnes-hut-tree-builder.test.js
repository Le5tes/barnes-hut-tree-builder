/**
 * @jest-environment node
 */

import { BarnesHutTreeBuilder } from '../src/barnes-hut-tree-builder';

describe('Barnes hut tree builder', () => {
  it('should exist', () => {
    expect(new BarnesHutTreeBuilder()).toBeTruthy();
  });

  it('should receive a new TreeBuilder object on initialisation', () => {
    const stubGetTreeBuilder = getStub();

    new BarnesHutTreeBuilder(stubGetTreeBuilder)
  
    expect(stubGetTreeBuilder.callCount).toEqual(1);
  });
  
  it('should be able to get the treebuilder method from wasm', async () => {
   const treeBuilder = await BarnesHutTreeBuilder.create();

   expect(treeBuilder.treeBuilder).toBeTruthy()
  });
  
  describe.only('buildToArray', () => {
    it('should return an array of nodes built from the bodies provided', async () => {
       const treeBuilder = await BarnesHutTreeBuilder.create();
       
       const result = treeBuilder.buildToArray([{mass: 100, posX: 10, posY: 10}]);
       
       expect(result).toEqual([[10,10,100,0,0,0,0,0,0,0]]);
    })
  });
});

const getStub = () => {
  const stub = () => {
      stub.callCount++;
    }
  stub.callCount = 0;
  return stub;
}
