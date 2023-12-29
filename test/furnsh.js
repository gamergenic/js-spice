const expect = require('chai').expect;
const { spice, getKernels, cacheGenericKernel } = require('..');

describe('furnsh', function() {
    it('should furnish a program with SPICE kernels.', 
        async function() {

            spice.kclear();
            const singleFilePathStr = await cacheGenericKernel('pck/a_old_versions/pck00009.tpc', 'test/data/naif/generic_kernels/pck/a_old_versions/pck00009.tpc');

            spice.furnsh(singleFilePathStr);

            expect(Array.isArray(spice.bodvrd("EARTH", "RADII"))).to.be.equal(true);
        });

    it('should furnish load an array of paths.', 
        async function() {

            spice.kclear();
            const kernelsToLoad = [
                'spk/planets/a_old_versions/de421.bsp',
                'pck/a_old_versions/pck00009.tpc',
                'lsk/a_old_versions/naif0009.tls',
              ];

            await getKernels(kernelsToLoad, 'test/data/naif/generic_kernels');
            const pathsArray = kernelsToLoad.map(kernel => './test/data/naif/generic_kernels/' + kernel);

            spice.furnsh(pathsArray);

            expect(Array.isArray(spice.bodvrd("EARTH", "RADII"))).to.be.equal(true);
        });

    it('should throw an error if kernel cannot be found', function() {
        function test(){
            spice.kclear();
            spice.furnsh("badpath");
        }

        expect(test).to.throw();
    });
    
    it('should not leave a signaled SPICE error after failure', function() {
        try{
            spice.kclear();
            spice.furnsh("badpath");
        }
        catch(error){
        }

        const failed = spice.failed();
        expect(failed).to.be.equal(false);
    });     
});            
