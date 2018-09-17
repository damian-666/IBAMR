import config.package

class Configure(config.package.GNUPackage):
  def __init__(self, framework):
    config.package.GNUPackage.__init__(self, framework)
    self.download  = ['http://ftp.mcs.anl.gov/pub/petsc/externalpackages/SAMRAI-v2.4.4p.tar.gz', 'https://computation-rnd.llnl.gov/SAMRAI/download/SAMRAI-v2.4.4.tar.gz']
    self.functions = []
    self.includes  = ['Box.h']
    if framework.argDB['DIM'] == 2:
        self.liblist = [['libSAMRAI.a', 'libSAMRAI2d_algs.a', 'libSAMRAI2d_appu.a', 'libSAMRAI2d_geom.a', 'libSAMRAI2d_hier.a', 'libSAMRAI2d_math_std.a', 'libSAMRAI2d_mesh.a', 'libSAMRAI2d_pdat_std.a', 'libSAMRAI2d_solv.a', 'libSAMRAI2d_xfer.a']]
    if framework.argDB['DIM'] == 3:
        self.liblist = [['libSAMRAI.a', 'libSAMRAI3d_algs.a', 'libSAMRAI3d_appu.a', 'libSAMRAI3d_geom.a', 'libSAMRAI3d_hier.a', 'libSAMRAI3d_math_std.a', 'libSAMRAI3d_mesh.a', 'libSAMRAI3d_pdat_std.a', 'libSAMRAI3d_solv.a', 'libSAMRAI3d_xfer.a']]
    self.pkgname   = 'SAMRAI-2.4.4'
    self.cxx       = 1
    return

  def setupHelp(self, help):
    import nargs
    help.addArgument(self, '-DIM=<spatial dimension>', nargs.ArgInt(None, 2, 'Specify the spatial dimension (eg. 2 or 3)'))

  def setupDependencies(self, framework):
    config.package.GNUPackage.setupDependencies(self, framework)
    self.setCompilers = framework.require('config.setCompilers', self)
    self.compilers    = framework.require('config.compilers', self)
    self.mpi  = framework.require('config.packages.MPI', self)
    self.hdf5 = framework.require('config.packages.hdf5', self)
    self.silo = framework.require('IBAMR.packages.silo', self)
    self.deps = [self.mpi, self.hdf5, self.silo]
    return

  def gitPreInstallCheck(self):
    '''Perhaps configure need to be built before install. This is intended to be overwritten by a subclass'''
    import urllib, os
    
    markFile = os.path.join(self.packageDir, '_patched')
    if not os.path.isfile(markFile):
      # Link headers
      output1,err1,ret1 = config.base.Configure.executeShellCommand('cd '+self.packageDir+' && ./source/scripts/includes --link', timeout=200, log = self.framework.log)
      # Patch source
      urllib.urlretrieve('https://github.com/IBAMR/IBAMR/releases/download/v0.1-rc1/SAMRAI-v2.4.4-patch-121212.gz', os.path.join(self.externalPackagesDir, 'SAMRAI-v2.4.4-patch-121212.gz'))
      self.framework.actions.addArgument(self.PACKAGE, 'Download', 'Downloaded v2.4.4-patch-121212 into '+self.externalPackagesDir)
      output2,err2,ret2 = config.base.Configure.executeShellCommand('cd '+self.packageDir+' && gunzip -c '+os.path.join(self.externalPackagesDir, 'SAMRAI-v2.4.4-patch-121212.gz')+' | patch -p2', timeout=200, log = self.framework.log)
      f = file(markFile, 'w')
      f.write('Patched and linked headers')
      f.close
    return

  def formGNUConfigureArgs(self):
    args = config.package.GNUPackage.formGNUConfigureArgs(self)
    # Fix broken configure check
    args.append('F77LIBFLAGS="'+' '.join(self.compilers.flibs)+'"')
    args.append('--with-MPICC='+self.setCompilers.CC)
    args.append('--with-hdf5='+self.hdf5.directory)
    args.append('--with-silo='+self.silo.directory)
    args.append('--enable-debug')
    args.append('--disable-opt')
    args.append('--enable-implicit-template-instantiation')
    args.append('--disable-deprecated')
    args.append('--without-hypre')
    args.append('--without-blaslapack')
    args.append('--without-cubes')
    args.append('--without-eleven')
    args.append('--without-kinsol')
    args.append('--without-petsc')
    args.append('--without-sundials')
    args.append('--without-x')
    args.append('--with-doxygen')
    args.append('--with-dot')
    # Completely broken shared libraries for Mac
    args.append('--disable-shared')
    return args
