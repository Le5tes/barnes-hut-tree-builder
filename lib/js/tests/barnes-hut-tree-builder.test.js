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

    new BarnesHutTreeBuilder({getTreeBuilder: stubGetTreeBuilder})
  
    expect(stubGetTreeBuilder.callCount).toEqual(1);
  });
  
  describe('#buildToArray', () => {
    let treeBuilder;
    let stubCore;

    beforeEach(() => {
      stubCore = {build: getStub()}
      treeBuilder = new BarnesHutTreeBuilder({getTreeBuilder: () => stubCore, _malloc: () => null, HEAPF64: {set: () => null}})
    });

    it('should call the core build function', () => {
      treeBuilder.buildToArray([])

      expect(stubCore.build.callCount).toEqual(1);
    });
  });

  describe('integration', () => {
    let treeBuilder

    beforeEach(async () => {
      treeBuilder = await BarnesHutTreeBuilder.create();
    });

    it('should be able to get the treebuilder method from wasm', async () => {
      expect(treeBuilder.treeBuilder).toBeTruthy()
    });

    describe('#buildToArray', () => {
      it('should return an array representing the nodes', () => {
        const bodies = [{
            mass: 100,
            posX: 515,
            posY: 300
          }];

        expect(treeBuilder.buildToArray(bodies)).toEqual([[100, 515, 300, 1000, 0, -1, -1, -1, -1, -1]]);
      })
    });
  });
});

const getStub = () => {
  const stub = () => {
      stub.callCount++;
      stub.lastCallArgs = Array.from(arguments)
    }
  stub.callCount = 0;
  return stub;
}
