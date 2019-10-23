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
});

const getStub = () => {
  const stub = () => {
      stub.callCount++;
    }
  stub.callCount = 0;
  return stub;
}
