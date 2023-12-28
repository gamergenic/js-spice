const expect = require('chai').expect;
const { spice } = require('..');

describe('prop2b', function() {
    // from https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/prop2b_c.html
    it('should Compute the state of a massless body at time t_0 + dt by applying \
the two-body force model to a given central mass and a given body \
state at time t_0.', function() {
        const mu = 3.9860043543609598e5;
        const r = 1e8;
        const speed = Math.sqrt(mu/r);
        const pi = 3.141592653589793238462643383279502884197;
        const t = pi * r / speed; 
        const pvinit = {
            "r": [0, r/Math.sqrt(2), r/Math.sqrt(2)],
            "v": [0, -speed/Math.sqrt(2), speed/Math.sqrt(2)]
        };
        const dt = 0;
    
        let actual = spice.prop2b(mu, pvinit, t);
    
        let expected = {
            "r": [-0.00000,-70710678.11865,-70710678.11865],
            "v": [0.00000,0.04464,-0.04464]
        };
    
        expect(actual.r[0]).to.be.closeTo(expected.r[0], 0.00001);
        expect(actual.r[1]).to.be.closeTo(expected.r[1], 0.00001);
        expect(actual.r[2]).to.be.closeTo(expected.r[2], 0.00001);
        expect(actual.v[0]).to.be.closeTo(expected.v[0], 0.00001);
        expect(actual.v[1]).to.be.closeTo(expected.v[1], 0.00001);
        expect(actual.v[2]).to.be.closeTo(expected.v[2], 0.00001);
      });
    

    it('should accept state as {r:[x,y,z],v:[dx,dy,dz]} arrays', function() {
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

    it('should throw an error with degenerate orbit', function() {
        function test(){
            const gm = 0;
            const state = {"r": [1,1,1], "v": [1,1,1]};
            const dt = 0;

            spice.prop2b(gm, state, dt);
        }

        expect(test).to.throw();
    });

    it('should throw an error with 4d r vector', function() {
        function test(){
            const gm = 0;
            const state = {"r": [1,1,1,1], "v": [1,0,0]};
            const dt = 0;

            spice.prop2b(gm, state, dt);
        }

        expect(test).to.throw();
    });

    it('should throw an error with 2d r vector', function() {
        function test(){
            const gm = 0;
            const state = {"r": [1,1], "v": [1,1,1]};
            const dt = 0;

            spice.prop2b(gm, state, dt);
        }

        expect(test).to.throw();
    });    
    
    it('should throw an error with string r.x value', function() {
        function test(){
            const gm = 0;
            const state = {"r": ["1",1,1], "v": [1,1,1]};
            const dt = 0;

            spice.prop2b(gm, state, dt);
        }

        expect(test).to.throw();
    });
    
    it('should throw an error with null r.x value', function() {
        function test(){
            const gm = 0;
            const state = {"r": [null,1,1], "v": [1,1,1]};
            const dt = 0;

            spice.prop2b(gm, state, dt);
        }

        expect(test).to.throw();
    });     
  
});
