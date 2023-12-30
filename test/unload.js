const expect = require('chai').expect;
const { spice, cacheGenericKernel } = require('..');

describe('unload', function() {
    it('should unload a SPICE kernel.', 
        async function() {

        spice.kclear();
        const singleFilePathStr = await cacheGenericKernel('pck/a_old_versions/pck00009.tpc', 'test/data/naif/generic_kernels/pck/a_old_versions/pck00009.tpc');

        spice.furnsh(singleFilePathStr);

        expect(Array.isArray(spice.bodvrd("EARTH", "RADII"))).to.be.equal(true);

        spice.unload(singleFilePathStr);

        function test(){
            spice.bodvrd("EARTH", "RADII");
        }

        // Expect after the clear we can't read earth's radii
        expect(test).to.throw();
    });
});            
