const expect = require('chai').expect;
const { spice } = require('..');

describe('prop2b', function() {
  it('should accept vec3 as array', function() {
    const gm = 100;
    const state = {"r": [1,1,1], "v": [1,0,0]};
    const dt = 0;

    let actual = spice.prop2b(gm, state, dt);

    let expected = {"r": [1,1,1], "v": [1,0,0]};

    expect(actual.r[0]).to.be.closeTo(expected.r[0], 0.0001);
    expect(actual.r[1]).to.be.closeTo(expected.r[1], 0.0001);
    expect(actual.r[2]).to.be.closeTo(expected.r[2], 0.0001);
    expect(actual.v[0]).to.be.closeTo(expected.v[0], 0.0001);
    expect(actual.v[1]).to.be.closeTo(expected.v[1], 0.0001);
    expect(actual.v[2]).to.be.closeTo(expected.v[2], 0.0001);
  });

  it('should throws an error with degenerate orbit', function() {
    function test(){
        const gm = 0;
        const state = {"r": [1,1,1], "v": [1,1,1]};
        const dt = 0;

        spice.prop2b(gm, state, dt);
    }

    expect(test).to.throw();
  });

  it('should throws an error with 4d r vector', function() {
    function test(){
        const gm = 0;
        const state = {"r": [1,1,1,1], "v": [1,1,1]};
        const dt = 0;

        spice.prop2b(gm, state, dt);
    }

    expect(test).to.throw();
  });
  
  it('should throws an error with string r.x value', function() {
    function test(){
        const gm = 0;
        const state = {"r": ["1",1,1], "v": [1,1,1]};
        const dt = 0;

        spice.prop2b(gm, state, dt);
    }

    expect(test).to.throw();
  });  
  
});
