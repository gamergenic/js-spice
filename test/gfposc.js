const expect = require('chai').expect;
const { spice, getKernels } = require('..');

describe('gfposc', function() {

    // Allow extra time as this is a computationally expensive operation.
    // Plus, we may need to download a number of kernels to run the test.
    this.timeout(60000);

    it('should determine time intervals for which a coordinate of an \
observer-target position vector satisfies a numerical constraint.',
    
    async function() {

        // taken from:
        // https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/req/gf.html
        const kernelsToLoad = [
            'lsk/a_old_versions/naif0009.tls',
            'pck/a_old_versions/pck00008.tpc',
            'spk/planets/a_old_versions/de421.bsp',
            'spk/satellites/a_old_versions/sat288.bsp',
            'spk/stations/a_old_versions/earthstns_itrf93_050714.bsp',
            'fk/stations/a_old_versions/earth_topo_050714.tf',
            'pck/a_old_versions/earth_070425_370426_predict.bpc',
        ];
    
    
        await getKernels(kernelsToLoad, 'test/data/naif/generic_kernels');   
    
        /*
        We'll consider Saturn to be visible from DSS-14 when
        Saturn has elevation above 6 degrees in the DSS-14
        topocentric reference frame DSS-14_TOPO. 
        
        Create a confinement window for the view period
        search. This window contains the start and stop times
        of the search interval.
        */
        
        const et0 = spice.str2et("2009 JAN 1");
        const et1 = spice.str2et("2009 JAN 5");
        const cnfine = [[et0, et1]];

        /*
            Set the observer, target and reference frame.
            */
        const obsrvr = "DSS-14";
        const target = "SATURN";
        const frame  = "DSS-14_TOPO";

        /*
        The coordinate system is latitudinal; in this system,
        in the DSS-14_TOPO frame, the coordinate "latitude"
        is equivalent to elevation.
        */
        const crdsys = "LATITUDINAL";
        const coord  = "LATITUDE";

        /*
        The relational operator for this search is "greater
        than" and the reference value is 6 degrees (converted
        to radians).
        */
        const relate = ">";
        const refval = 6.0 * spice.rpd();

        /*
        We're looking for the apparent position of Saturn,
        so apply corrections for light time and stellar
        aberration.
        */
        const abcorr = "LT+S";

        /*
        Set the step size for this search. The step must
        be shorter than the shortest interval over which
        the elevation is increasing or decreasing.
        We pick a conservative value: 6 hours. Units
        expected by SPICE are TDB seconds.
        */
        const step   =  spice.spd() / 4;

        /*
        The adjustment value isn't used for this search;
        set it to 0.
        */
        const adjust = 0.0;

        /*
        The number of intervals will be left as default
        and the argument omitted.
    
        Execute the search.
        */        

        const actual = spice.gfposc(
            target, frame, abcorr, obsrvr,
            crdsys, coord, relate, refval,
            adjust, step,  cnfine);


        /*
        Display the times of rise and set.
        */

        /*
        console.log( "\nTimes of Saturn rise/set as seen from DSS-14:\n\n" );

        if(Array.isArray(result)){
            result.forEach((window)=>{
                et0str = spice.timout(window[0], timeformat);
                et1str = spice.timout(window[1], timeformat);
                console.log(`${et0str} ${et1str}`);
            });
        }
        */

        expect(actual.length).to.be.equal(4);

        const TIMFMT = "YYYY MON DD HR:MN:SC.###### TDB::RND::TDB";
        expect(spice.timout(actual[0][0],  TIMFMT)).to.be.equal("2009 JAN 01 06:52:14.372881 TDB");      
        expect(spice.timout(actual[0][1],  TIMFMT)).to.be.equal("2009 JAN 01 18:20:41.050047 TDB");      
        expect(spice.timout(actual[1][0],  TIMFMT)).to.be.equal("2009 JAN 02 06:48:17.641267 TDB");      
        expect(spice.timout(actual[1][1],  TIMFMT)).to.be.equal("2009 JAN 02 18:16:45.859623 TDB");      
        expect(spice.timout(actual[2][0],  TIMFMT)).to.be.equal("2009 JAN 03 06:44:20.383435 TDB");      
        expect(spice.timout(actual[2][1],  TIMFMT)).to.be.equal("2009 JAN 03 18:12:50.385687 TDB");      
        expect(spice.timout(actual[3][0],  TIMFMT)).to.be.equal("2009 JAN 04 06:40:22.601451 TDB");      
        expect(spice.timout(actual[3][1],  TIMFMT)).to.be.equal("2009 JAN 04 18:08:54.628325 TDB");       
    });
});
