// test/test.js
const expect = require('chai').expect;
const { spice } = require('..'); // Adjust the path based on your project structure

describe('mtxm', function() {
  it('matrix times identity should equal transpose', function() {
    let m1 = [[1, 2, 3], [4,5,6], [7,8,9]];
    let m2 = [[1, 0, 0], [0,1,0], [0,0,1]];

    let actual = spice.mtxm(m1, m2);

    let expected = [[1, 4, 7], [2,5,8], [3,6,9]];
    for (let i = 0; i < actual.length; i++) {
      for (let j = 0; j < actual[i].length; j++) {
        expect(actual[i][j]).to.be.closeTo(expected[i][j], 0.0001);
      }
    }
  });
});
