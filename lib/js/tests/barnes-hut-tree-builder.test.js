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
      stubCore = {build: getStub(), getTreeLength: getStub()}
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

        const width = 1000;
        const cornerX = 0;
        const cornerY = 0;

        expect(treeBuilder.buildToArray(bodies, width, cornerX, cornerY)).toEqual([[515, 300, 100, 1000, 0, 0, -1, 0, -1, -1, -1, -1]]);
      });
      
      it('should be able to build complicated trees', () => {
         const bodies = [{
            mass: 100,
            posX: 515,
            posY: 300
          }, {
            mass: 55,
            posX: 101, 
            posY: 23
          }, {
            mass: 692,
            posX: 12, 
            posY: 992
          }, {
            mass: 47,
            posX: 579, 
            posY: 453
          }, {
            mass: 300,
            posX: 109, 
            posY: 645
          }];
          
        const width = 1000;
        const cornerX = 0;
        const cornerY = 0;

        const result = treeBuilder.buildToArray(bodies, width, cornerX, cornerY)

        const expectedResult = [
          [104.9179229480737, 781.0050251256281, 1194, 1000, 0, 0, -1, -1, 1, 2, 3, 4],
          [101, 23, 55, 500, 0, 0, 0, 1, -1, -1, -1, -1],
          [535.4625850340136, 348.9183673469388, 147, 500, 500, 0, 0, -1, 5, 6, 7, 8],
          [41.33467741935484, 887.0604838709677, 992, 500, 0, 500, 0, -1, 13, 14, 15, 16],
          [0, 0, 0, 500, 500, 500, 0, -1, -1, -1, -1, -1],
          [0, 0, 0, 250, 500, 0, 2, -1, -1, -1, -1, -1],
          [0, 0, 0, 250, 750, 0, 2, -1,  -1,  -1, -1, -1],
          [535.4625850340136, 348.9183673469388, 147, 250, 500, 250, 2, -1, 9, 10, 11, 12],
          [0, 0, 0, 250, 750, 250, 2, -1, -1, -1, -1, -1],
          [515, 300, 100, 125, 500, 250, 7, 0, -1, -1, -1, -1],
          [0, 0, 0, 125, 625, 250, 7, -1, -1, -1, -1, -1],
          [579, 453, 47, 125, 500, 375, 7, 3, -1, -1, -1, -1],
          [0, 0, 0, 125, 625, 375, 7, -1, -1, -1, -1, -1],
          [109, 645, 300, 250, 0, 500, 3, 4, -1, -1, -1, -1],
          [0, 0, 0, 250, 250, 500, 3, -1, -1, -1, -1, -1],
          [12, 992, 692, 250, 0, 750, 3, 2, -1, -1, -1, -1],
          [0, 0, 0, 250, 250, 750, 3, -1, -1, -1, -1, -1]
        ]

        expect(result).toEqual(expectedResult)
      });

      it('should return the correct array length for trees where the internal array was resized', () => {
        const bodies = [{
            mass: 100,
            posX: 10,
            posY: 10
          },{
            mass: 100,
            posX: 10,
            posY: 10.1
          }];

        const width = 3000;
        const cornerX = -1500;
        const cornerY = -1500;

        const result = treeBuilder.buildToArray(bodies, width, cornerX, cornerY)

        expect(result.length).toEqual(57);
      });
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
