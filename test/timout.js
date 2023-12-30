const expect = require('chai').expect;
const { spice, et_now } = require('..');

describe('timout', function() {
  it('Convert an input epoch represented in TDB seconds past the TDB \
  epoch of J2000 to a character string formatted to the \
  specifications of a user\'s format picture.',
   function() {

    const et = 757234367.172871;
    const actual = spice.timout(et, 'MON DD,YYYY  HR:MN:SC.#### (TDB) ::TDB');

    const expected = 'DEC 30,2023  18:52:47.1728 (TDB)';

    expect(actual).to.be.equal(expected); 
  });
});
