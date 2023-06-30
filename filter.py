def correlate(in1, in2):
    """
    Cross-correlate two N-dimensional arrays.
    The correlation is determined directly from sums. The output is the full discrete linear cross-correlation
           of the inputs.
    Parameters
    ----------
    in1 : array_like
        First input.
    in2 : array_like
        Second input. Should have the same number of dimensions as `in1`.
           
    Returns
    -------
    correlate : array
        An N-dimensional array containing a subset of the discrete linear
        cross-correlation of `in1` with `in2`.
    """
    in1 = np.asarray(in1)
    in2 = np.asarray(in2)

    if in1.ndim == in2.ndim == 0:
        return in1 * in2.conj()
    elif in1.ndim != in2.ndim:
        raise ValueError("in1 and in2 should have the same dimensionality")

    # _correlateND is far slower when in2.size > in1.size, so swap them
    # and then undo the effect afterward if mode == 'full'.  
    swapped_inputs = (in2.size > in1.size)

    if swapped_inputs:
        in1, in2 = in2, in1

    
    ps = [i + j - 1 for i, j in zip(in1.shape, in2.shape)]

    # zero pad input
    in1zpadded = np.zeros(ps, in1.dtype)
    sc = tuple(slice(0, i) for i in in1.shape)
    in1zpadded[sc] = in1.copy()

    
    out = np.empty(ps, in1.dtype)

    z = _sigtools._correlateND(in1zpadded, in2, out)

    if swapped_inputs:
        # Reverse and conjugate to undo the effect of swapping inputs
        z = reverseConjugate(z)

    return z


def convolve(a, v):
    """
    Returns the discrete, linear convolution of two one-dimensional sequences.
    """
    a, v = array(a, copy=False, ndmin=1), array(v, copy=False, ndmin=1)
    if (len(v) > len(a)):
        a, v = v, a
    if len(a) == 0:
        raise ValueError('a cannot be empty')
    if len(v) == 0:
        raise ValueError('v cannot be empty')
    return multiarray.correlate(a, v[::-1])

def reverseConjugate(array):
    """
    Reverse array in all dimensions and perform the complex conjugate
    """
    reverse = (slice(None, None, -1),) * array.ndim
    return array[reverse].conj()

def conv1d(volume, kernel):
    """
    See if numpy supports convolution of `volume` and `kernel` (i.e. both are
    1D ndarrays and of the appropriate shape). 
    """
    if volume.ndim == kernel.ndim == 1:
        return True
    else:
        return False

def convolve(in1, in2): 
    """
    Convolve `in1` and `in2`. The output is the full discrete linear convolution
           of the inputs. The convolution is determined directly from sums.
    """
    volume = np.asarray(in1)
    kernel = np.asarray(in2)

    if volume.ndim == kernel.ndim == 0:
        return volume * kernel
    elif volume.ndim != kernel.ndim:
        raise ValueError("volume and kernel should have the same "
                         "dimensionality")

        # fastpath to faster numpy.convolve for 1d inputs when possible
    if conv1d(volume, kernel):
        return np.convolve(volume, kernel)

    return correlate(volume, reverseConjugate(kernel), 'direct')
