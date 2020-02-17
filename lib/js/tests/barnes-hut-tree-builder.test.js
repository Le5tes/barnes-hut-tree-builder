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
  
  describe('#build', () => {
    let treeBuilder;
    let stubCore;

    beforeEach(() => {
      stubCore = {build: getStub(), getTreeLength: getStub()}
      treeBuilder = new BarnesHutTreeBuilder({getTreeBuilder: () => stubCore, _malloc: () => null, HEAPF64: {set: () => null}})
    });
    
    it('should call buildToArray', () => {
      treeBuilder.buildToArray = getStub();
       treeBuilder.buildToArray.returnVal = [[100,100,100,1000,0,0,-1,-1,-1,-1,-1,-1]]
      
      treeBuilder.build([]);
      
      expect(treeBuilder.buildToArray.callCount).toEqual(1);
    });
    
    it('should build a tree of objects from the returned array', () => {
      treeBuilder.buildToArray = getStub();
      treeBuilder.buildToArray.returnVal = [
        [100,100,100,1000,0,0,-1,-1,1,2,-1,3],
        [100,100,100,1000,0,0,0,-1,6,-1,-1,4],
        [100,100,100,1000,0,0,0,-1,-1,5,-1,7],
        [100,100,100,1000,0,0,0,0,-1,-1,-1,-1],
        [100,100,100,1000,0,0,1,1,-1,-1,-1,-1],
        [100,100,100,1000,0,0,2,2,-1,-1,-1,-1],
        [100,100,100,1000,0,0,1,3,-1,-1,-1,-1],
        [100,100,100,1000,0,0,2,4,-1,-1,-1,-1],
        ]
        
      const bodies = [{mass: 1},{mass: 2},{mass: 3},{mass: 4},{mass: 5}]
        
      const expectedVal = {
        positionX: 100,
        positionY: 100,
        mass: 100,
        width: 1000,
        cornerX: 0,
        cornerY: 0,
        body: undefined,
        subnodes: [{
          positionX: 100,
          positionY: 100,
          mass: 100,
          width: 1000,
          cornerX: 0,
          cornerY: 0,
          body: undefined,
          subnodes: [{
            positionX: 100,
            positionY: 100,
            mass: 100,
            width: 1000,
            cornerX: 0,
            cornerY: 0,
            body: {mass: 4},
            subnodes: []
          }, {
            positionX: 100,
            positionY: 100,
            mass: 100,
            width: 1000,
            cornerX: 0,
            cornerY: 0,
            body: {mass: 2},
            subnodes: []
          }]
        }, {
          positionX: 100,
          positionY: 100,
          mass: 100,
          width: 1000,
          cornerX: 0,
          cornerY: 0,
          body: undefined,
          subnodes: [{
            positionX: 100,
            positionY: 100,
            mass: 100,
            width: 1000,
            cornerX: 0,
            cornerY: 0,
            body: {mass: 3},
            subnodes: []
          }, {
            positionX: 100,
            positionY: 100,
            mass: 100,
            width: 1000,
            cornerX: 0,
            cornerY: 0,
            body: {mass: 5},
            subnodes: []
          }]
        }, {
          positionX: 100,
          positionY: 100,
          mass: 100,
          width: 1000,
          cornerX: 0,
          cornerY: 0,
          body: {mass: 1},
          subnodes: []
        }]
      }
        
      expect(treeBuilder.build(bodies)).toEqual(expectedVal);
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
            positionX: 515,
            positionY: 300
          }];

        const width = 1000;
        const cornerX = 0;
        const cornerY = 0;

        expect(treeBuilder.buildToArray(bodies, width, cornerX, cornerY)).toEqual([[515, 300, 100, 1000, 0, 0, -1, 0, -1, -1, -1, -1]]);
      });
      
      it('should be able to build complicated trees', () => {
         const bodies = [{
            mass: 100,
            positionX: 515,
            positionY: 300
          }, {
            mass: 55,
            positionX: 101, 
            positionY: 23
          }, {
            mass: 692,
            positionX: 12, 
            positionY: 992
          }, {
            mass: 47,
            positionX: 579, 
            positionY: 453
          }, {
            mass: 300,
            positionX: 109, 
            positionY: 645
          }];
          
        const width = 1000;
        const cornerX = 0;
        const cornerY = 0;

        const result = treeBuilder.buildToArray(bodies, width, cornerX, cornerY)

        const expectedResult = [
          [104.9179229480737, 781.0050251256281, 1194, 1000, 0, 0, -1, -1, 2, 1, 3, -1],
          [535.4625850340136, 348.9183673469388, 147, 500, 500, 0, 0, -1, -1, -1, 4, -1],
          [101, 23, 55, 500, 0, 0, 0, 1, -1, -1, -1, -1],
          [41.33467741935484, 887.0604838709677, 992, 500, 0, 500, 0, -1, 8, -1, 7, -1],
          [535.4625850340136, 348.9183673469388, 147, 250, 500, 250, 1, -1, 5, -1, 6, -1],
          [515, 300, 100, 125, 500, 250, 4, 0, -1, -1, -1, -1],
          [579, 453, 47, 125, 500, 375, 4, 3, -1, -1, -1, -1],
          [12, 992, 692, 250, 0, 750, 3, 2, -1, -1, -1, -1],
          [109, 645, 300, 250, 0, 500, 3, 4, -1, -1, -1, -1],
          
        ]

        expect(result).toEqual(expectedResult)
      });

      it('should return the correct array length for trees where the internal array was resized', () => {
        const bodies = [{
            mass: 100,
            positionX: 10,
            positionY: 10
          },{
            mass: 100,
            positionX: 10,
            positionY: 10.1
          }];

        const width = 3000;
        const cornerX = -1500;
        const cornerY = -1500;

        const result = treeBuilder.buildToArray(bodies, width, cornerX, cornerY)

        expect(result.length).toEqual(16);
      });

      it('should not throw errors when called with two bodies outside of bounds', () => {
        const bodies = [{
          mass: 100,
          positionX: 515,
          positionY: 300
        },{
          mass: 100,
          positionX: 1005,
          positionY: 300
        },{
          mass: 100,
          positionX: 1015,
          positionY: 300
        }];

        const width = 1000;
        const cornerX = 0;
        const cornerY = 0;

        expect(() => treeBuilder.buildToArray(bodies, width, cornerX, cornerY)).not.toThrowError();
      });
    });
    
    describe('build', () => {
      it('should return an object tree containing the bodies passed in', () => {
        const bodies = [{
            mass: 100,
            positionX: 515,
            positionY: 300
          }];

        const width = 1000;
        const cornerX = 0;
        const cornerY = 0;
        
        const expectedValue = {
          mass: 100,
          positionX: 515,
          positionY: 300,
          width: 1000,
          cornerX: 0,
          cornerY: 0,
          body: {
            mass: 100,
            positionX: 515,
            positionY: 300
          },
          subnodes: []
        }
        
        expect(treeBuilder.build(bodies, width, cornerX, cornerY)).toEqual(expectedValue);
      });
    });
  });
});

const getStub = () => {
  const stub = () => {
      stub.callCount++;
      stub.lastCallArgs = Array.from(arguments)
      return stub.returnVal;
    }
  stub.callCount = 0;
  return stub;
}
