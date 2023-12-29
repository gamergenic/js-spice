const expect = require('chai').expect;
const { spice, getKernels, cacheGenericKernel } = require('..');

describe('kclear', function() {
    it('should clear loaded kernels.', 
        async function() {

        spice.kclear();

        await getKernels('pck/a_old_versions/pck00009.tpc', 'test/data/naif/generic_kernels');

        expect(Array.isArray(spice.bodvrd("EARTH", "RADII"))).to.be.equal(true);

        spice.kclear();

        function test(){
            spice.bodvrd("EARTH", "RADII");
        }

        // Expect after the clear we can't read earth's radii
        expect(test).to.throw();
    });
});            
