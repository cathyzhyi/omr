/*******************************************************************************
 *
 * (c) Copyright IBM Corp. 2000, 2017
 *
 *  This program and the accompanying materials are made available
 *  under the terms of the Eclipse Public License v1.0 and
 *  Apache License v2.0 which accompanies this distribution.
 *
 *      The Eclipse Public License is available at
 *      http://www.eclipse.org/legal/epl-v10.html
 *
 *      The Apache License v2.0 is available at
 *      http://www.opensource.org/licenses/apache2.0.php
 *
 * Contributors:
 *    Multiple authors (IBM Corp.) - initial implementation and documentation
 *******************************************************************************/

#ifndef TESTFE_INCL
#define TESTFE_INCL

#include <vector>
#include "codegen/FrontEnd.hpp"
#include "env/FEBase.hpp"
#include "env/jittypes.h"
#include "runtime/JBJitConfig.hpp"
#include "runtime/CodeCache.hpp"

namespace TR { class GCStackAtlas; }
namespace OMR { struct MethodMetaDataPOD; }
class TR_ResolvedMethod;

namespace TR
{

template <> struct FETraits<JitBuilder::FrontEnd>
   {
   typedef JitBuilder::JitConfig      JitConfig;
   typedef TR::CodeCacheManager CodeCacheManager;
   typedef TR::CodeCache        CodeCache;
   static const size_t  DEFAULT_SEG_SIZE = (128 * 1024); // 128kb
   };

}

namespace JitBuilder
{

class FrontEnd : public TR::FEBase<FrontEnd>
   {
   private:
   static FrontEnd   *_instance; /* singleton */

   public:
   FrontEnd();
   static FrontEnd *instance()  { TR_ASSERT(_instance, "bad singleton"); return _instance; }

   virtual void reserveTrampolineIfNecessary(TR::Compilation *comp, TR::SymbolReference *symRef, bool inBinaryEncoding);

#if defined(TR_TARGET_S390)
   virtual void generateBinaryEncodingPrologue(TR_BinaryEncodingData *beData, TR::CodeGenerator *cg);
   virtual bool getS390SupportsHPRDebug() { return false; }
#endif

   virtual intptrj_t methodTrampolineLookup(TR::Compilation *comp, TR::SymbolReference *symRef,  void *currentCodeCache);

  TR_ResolvedMethod * createResolvedMethod(TR_Memory * trMemory, TR_OpaqueMethodBlock * aMethod,
                                            TR_ResolvedMethod * owningMethod, TR_OpaqueClassBlock *classForNewInstance);


   void encodeStackMap(
      TR_GCStackMap *map,
      uint8_t *location,
      bool encodeFourByteOffsets,
      uint32_t bytesPerStackMap,
      TR::Compilation *comp);

   bool mapsAreIdentical(
      TR_GCStackMap *mapCursor,
      TR_GCStackMap *nextMapCursor,
      TR::GCStackAtlas *stackAtlas,
      TR::Compilation *comp);

   uint8_t *createStackAtlas(
      bool encodeFourByteOffsets,
      uint32_t numberOfSlotsMapped,
      uint32_t bytesPerStackMap,
      uint8_t *encodedAtlasBaseAddress,
      uint32_t atlasSizeInBytes,
      TR::Compilation *comp);

   uint32_t
      calculateSizeOfStackAtlas(
      bool encodeFourByteOffsets,
      uint32_t numberOfSlotsMapped,
      uint32_t bytesPerStackMap,
      TR::Compilation *comp);

   };

} // namespace JitBuilder

namespace TR
{
class FrontEnd : public JitBuilder::FrontEnd
   {
   public:
   FrontEnd();
   };

} // namespace TR

#endif

