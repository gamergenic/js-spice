const expect = require('chai').expect;
const { spice, cacheGenericKernel } = require('..');


describe('pckfrm', 
    function() {
    it('should find the set of reference frame class ID codes of all frames \
in a specified binary PCK file', 
    async function() {

        const singleFilePathStr = await cacheGenericKernel('pck/a_old_versions/earth_070425_370426_predict.bpc', 'test/data/naif/generic_kernels/pck/a_old_versions/earth_070425_370426_predict.bpc');

        const actual = spice.pckfrm(singleFilePathStr);

        const expected = [3000];

        expect(actual).to.be.deep.equal(expected);
    });
});



