/*!
 * \file rrset.h
 *
 * \author Lubos Slovak <lubos.slovak@nic.cz>
 * \author Jan Kadlec <jan.kadlec@nic.cz>
 *
 * \brief RRSet structure and API for manipulating it.
 *
 * \addtogroup libknot
 * @{
 */
/*  Copyright (C) 2013 CZ.NIC, z.s.p.o. <knot-dns@labs.nic.cz>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _KNOT_RRSET_H_
#define _KNOT_RRSET_H_

#include <stdint.h>
#include <stdbool.h>

#include "common/mempattern.h"

#include "libknot/dname.h"

struct knot_compr;
struct knot_node;

/*----------------------------------------------------------------------------*/
/*!
 * \brief Structure for representing an RRSet.
 *
 * For definition of a RRSet see RFC2181, Section 5.
 *
 * As all RRs within a RRSet share the same OWNER, TYPE, CLASS and TTL (see
 * Section 5.2 of RFC2181), there is no need to duplicate these data in the
 * program. Distinct Resource Records are thus represented only as distinct
 * RDATA sections of corresponding RRs.
 */

struct knot_rrset {
	knot_dname_t *owner; /*!< Domain name being the owner of the RRSet. */
	uint16_t type; /*!< TYPE of the RRset. */
	uint16_t rclass; /*!< CLASS of the RRSet. */
	uint16_t rr_count;
	/*! \brief RDATA array (for all RRs). DNAMEs stored as full,
	 *         uncompressed wire. Binary data stored in wireformat order.
	 *         Each RR is prepended with RDATA length and TTL, respectively.
	 */
	uint8_t *rrs;
	/* Optional fields. */
	struct knot_node **additional; /*!< Additional records. */
};

typedef struct knot_rrset knot_rrset_t;

/*----------------------------------------------------------------------------*/

typedef enum {
	KNOT_RRSET_COMPARE_PTR,
	KNOT_RRSET_COMPARE_HEADER,
	KNOT_RRSET_COMPARE_WHOLE
} knot_rrset_compare_type_t;

typedef enum  {
	KNOT_RRSET_DUPL_MERGE,
	KNOT_RRSET_DUPL_REPLACE,
	KNOT_RRSET_DUPL_SKIP
} knot_rrset_dupl_handling_t;

/*----------------------------------------------------------------------------*/

/*!
 * \brief Creates a new RRSet with the given properties.
 *
 * The created RRSet contains no RDATAs (i.e. is actually empty).
 *
 * \param owner OWNER of the RRSet.
 * \param type TYPE of the RRSet.
 * \param rclass CLASS of the RRSet.
 *
 * \return New RRSet structure or NULL if an error occured.
 */
knot_rrset_t *knot_rrset_new(knot_dname_t *owner, uint16_t type,
                             uint16_t rclass,
                             mm_ctx_t *mm);

/*!
 * \brief Creates a new RRSet according to given template RRSet.
 *
 * OWNER, TYPE, CLASS, and TTL values from template RRSet are used.
 *
 * \param tmp  RRSet template.
 *
 * \return New RRSet, NULL if an error occured.
 */
knot_rrset_t *knot_rrset_new_from(const knot_rrset_t *tpl, mm_ctx_t *mm);

/*!
 * \brief Adds the given RDATA to the RRSet.
 *
 * \param rrset RRSet to add the RDATA to.
 * \param rdata RDATA to add to the RRSet.
 * \param size Size of RDATA.
 * \param mm Memory context.
 *
 * \retval KNOT_EINVAL on wrong arguments.
 * \retval KNOT_EOK on success.
 */
int knot_rrset_add_rr(knot_rrset_t *rrset, const uint8_t *rdata,
                      const uint16_t size, const uint32_t ttl,
                      mm_ctx_t *mm);

/*!
 * \brief Creates RDATA memory and returns a pointer to it.
 *        If the RRSet is not empty, function will return a memory
 *        pointing to a beginning of a new RR. (Indices will be handled as well)
 *
 * \param rrset RRSet to add the RDATA to.
 * \param size Size of RR RDATA (Size in internal representation)
 * \param mm Memory context.
 *
 * \return Pointer to memory to be written to.
 * \retval NULL if arguments are invalid
 */
uint8_t* knot_rrset_create_rr(knot_rrset_t *rrset, const uint16_t size,
                              const uint32_t ttl, mm_ctx_t *mm);

/*!
 * \brief Adds RRSIG signatures to this RRSet.
 *
 * \param rrset RRSet to add the signatures into.
 * \param rrsigs Set of RRSIGs covering this RRSet.
 *
 * \retval KNOT_EOK
 * \retval KNOT_EINVAL
 */
int knot_rrset_set_rrsigs(knot_rrset_t *rrset, knot_rrset_t *rrsigs);

/*!
 * \brief Adds RRSIG signatures to this RRSet.
 *
 * \param rrset RRSet to add the signatures into.
 * \param rrsigs Set of RRSIGs covering this RRSet.
 * \param dupl Merging strategy.
 *
 * \retval KNOT_EOK if no merge was needed.
 * \retval 1 if merge was needed.
 * \retval 2 if rrsig was not first, but is was skipped.
 * \retval KNOT_EINVAL on faulty arguments or rrsig does not belong to this rrset.
 */
//TODO test
int knot_rrset_add_rrsigs(knot_rrset_t *rrset, knot_rrset_t *rrsigs,
                          knot_rrset_dupl_handling_t dupl);

/*!
 * \brief Returns the Owner of the RRSet.
 *
 * \param rrset RRSet to get the Owner of.
 *
 * \return Owner of the given RRSet.
 */
const knot_dname_t *knot_rrset_owner(const knot_rrset_t *rrset);

/*!
 * \brief Returns the Owner of the RRSet.
 *
 * \param rrset RRSet to get the Owner of.
 *
 * \return Owner of the given RRSet.
 */
knot_dname_t *knot_rrset_get_owner(const knot_rrset_t *rrset);

/*!
 * \brief Set rrset owner to specified dname.
 *
 * Previous owner will be replaced if exist.
 *
 * \param rrset Specified RRSet.
 * \param owner New owner dname.
 */
int knot_rrset_set_owner(knot_rrset_t *rrset, const knot_dname_t *owner);

void knot_rrset_set_class(knot_rrset_t *rrset, uint16_t rclass);

/*!
 * \brief Returns the TYPE of the RRSet.
 *
 * \param rrset RRSet to get the TYPE of.
 *
 * \return TYPE of the given RRSet.
 */
uint16_t knot_rrset_type(const knot_rrset_t *rrset);

/*!
 * \brief Returns the CLASS of the RRSet.
 *
 * \param rrset RRSet to get the CLASS of.
 *
 * \return CLASS of the given RRSet.
 */
uint16_t knot_rrset_class(const knot_rrset_t *rrset);

/*!
 * \brief Returns RDATA of RR on given position.
 *
 * \param rrset RRSet to get the RDATA from.
 * \param pos Position of RR to get.
 *
 * \retval NULL if no RDATA on rdata_pos exist.
 * \return Pointer to RDATA on given position if successfull.
 */
uint8_t *knot_rrset_rr_rdata(const knot_rrset_t *rrset, size_t pos);

/*!
 * \brief Returns size of an RR RDATA on a given position.
 *
 * \param rrset RRSet holding RR RDATA.
 * \param pos RR position.
 *
 * \retval 0 on error.
 * \return Item size on success.
 */
uint16_t knot_rrset_rr_size(const knot_rrset_t *rrset, size_t pos);
uint32_t knot_rrset_rr_ttl(const knot_rrset_t *rrset, size_t pos);
void knot_rrset_rr_set_ttl(const knot_rrset_t *rrset, size_t pos, uint32_t ttl);

bool knot_rrset_rdata_equal(const knot_rrset_t *r1, const knot_rrset_t *r2);

/*!
 * \brief Compares two RRSets for equality.
 *
 * \param r1 First RRSet.
 * \param r2 Second RRSet.
 * \param cmp Type of comparison to perform.
 *
 * \retval 1 if RRSets are equal.
 * \retval 0 if RRSets are not equal.
 * \retval < 0 if error occured.
 */
int knot_rrset_equal(const knot_rrset_t *r1,
                     const knot_rrset_t *r2,
                     knot_rrset_compare_type_t cmp);

int knot_rrset_deep_copy(const knot_rrset_t *from, knot_rrset_t **to,
                         mm_ctx_t *mm);

/*!
 * \brief Destroys the RRSet structure.
 *
 * Does not destroy the OWNER domain name structure, nor the signatures, as
 * these may be used elsewhere.
 *
 * Does not destroy RDATA structures neither, as they need special processing.
 *
 * Also sets the given pointer to NULL.
 *
 * \param rrset RRset to be destroyed.
 */
void knot_rrset_free(knot_rrset_t **rrset);

/*!
 * \brief Destroys the RRSet structure and all its substructures.
 *
 * Also sets the given pointer to NULL.
 *
 * \param rrset RRset to be destroyed.
 * \param free_owner Set to 0 if you do not want the owner domain name to be
 *                   destroyed also. Set to <> 0 otherwise.
 */
void knot_rrset_deep_free(knot_rrset_t **rrset, int free_owner, mm_ctx_t *mm);

int knot_rrset_to_wire(const knot_rrset_t *rrset, uint8_t *wire, size_t *size,
                       size_t max_size, uint16_t *rr_count, struct knot_compr *compr);

/*!
 * \brief Write one RR from RRSet.
 */
int knot_rrset_to_wire_one(const knot_rrset_t *rrset, uint16_t rr_number,
                           uint8_t *wire, size_t max_size, size_t *outsize,
                           struct knot_compr *compr);

/*!
 * \brief Merges two RRSets.
 *
 * Merges \a r1 into \a r2 by concatenating the list of RDATAs in \a r2 after
 * the list of RDATAs in \a r1. You must not
 * destroy the RDATAs in \a r2 as they are now identical to RDATAs in \a r1.
 * (You may use function knot_rrset_free() though, as it does not touch RDATAs).
 *
 * \note Member \a rrsigs is preserved from the first RRSet.
 *
 * \param r1 Pointer to RRSet to be merged into.
 * \param r2 Poitner to RRSet to be merged.
 *
 * \retval KNOT_EOK
 * \retval KNOT_EINVAL if the RRSets could not be merged, because their
 *         Owner, Type, Class or TTL does not match.
 */
int knot_rrset_merge(knot_rrset_t *rrset1, const knot_rrset_t *rrset2,
                     mm_ctx_t *mm);
/*! \brief Merges without with duplicate check, with sort. */
int knot_rrset_merge_sort(knot_rrset_t *rrset1, const knot_rrset_t *rrset2,
                          int *merged, int *deleted_rrs, mm_ctx_t *mm);

/*!
 * \brief Sort RDATA in RRSet to be in caonical order.
 * \todo Not optimal, rewrite!
 *
 * \param rrset  RRSet to be sorted.
 * \return Error code, KNOT_EOK when successful.
 */
int knot_rrset_sort_rdata(knot_rrset_t *rrset);

/*!
 * \brief Return true if the RRSet is an NSEC3 related type.
 *
 * \param rr RRSet.
 */
bool knot_rrset_is_nsec3rel(const knot_rrset_t *rr);

void knot_rrset_dump(const knot_rrset_t *rrset);

//TODO test
int rrset_serialize(const knot_rrset_t *rrset, uint8_t *stream, size_t *size);
uint64_t rrset_binary_size(const knot_rrset_t *rrset);

//TODO test
int rrset_serialize_alloc(const knot_rrset_t *rrset, uint8_t **stream,
                          size_t *size);

//TODO test
int rrset_deserialize(const uint8_t *stream, size_t *stream_size,
                      knot_rrset_t **rrset);

/* \brief Adds RR on 'pos' position from 'source' to 'dest' */
int knot_rrset_add_rr_from_rrset(knot_rrset_t *dest, const knot_rrset_t *source,
                                 size_t rdata_pos, mm_ctx_t *mm);
/* \brief Removes RRs contained in 'what' RRSet from 'from' RRSet.
 *        Deleted RRs are returned in 'rr_deleted' */
int knot_rrset_remove_rr_using_rrset(knot_rrset_t *from,
                                     const knot_rrset_t *what,
                                     knot_rrset_t **rr_deleted, mm_ctx_t *mm);
/* \brief Removes RRs contained in 'what' RRSet from 'from' RRSet. */
int knot_rrset_remove_rr_using_rrset_del(knot_rrset_t *from,
                                         const knot_rrset_t *what,
                                         mm_ctx_t *mm);
/* \brief Finds RR at 'pos' position in 'rr_reference' RRSet in 
         'rr_search_in' RRSet. Position returned in 'pos_out'. */
int knot_rrset_find_rr_pos(const knot_rrset_t *rr_search_in,
                           const knot_rrset_t *rr_reference, size_t pos,
                           size_t *pos_out);
/* \brief Creates one RR from wire, stores it into 'rrset'. */
int knot_rrset_rdata_from_wire_one(knot_rrset_t *rrset,
                                   const uint8_t *wire, size_t *pos,
                                   size_t total_size, uint32_t ttl, size_t rdlength,
                                   mm_ctx_t *mm);

int rrset_rdata_compare_one(const knot_rrset_t *rrset1,
                            const knot_rrset_t *rrset2,
                            size_t pos1, size_t pos2);

/*!
 * \brief Checks whether the given type requires additional processing.
 *
 * Only MX, NS and SRV types require additional processing.
 *
 * \param rrtype Type to check.
 *
 * \retval <> 0 if additional processing is needed for \a qtype.
 * \retval 0 otherwise.
 */
int rrset_additional_needed(uint16_t rrtype);

/*!
 * \brief Creates RRSIG record from node RRSIGs for given RRSet.
 *
 * \param rrsigs   Node RRSIGs.
 * \param type     Type to cover.
 * \param out_sig  Output RRSIG.
 * \param mm       Memory context.
 *
 * \return KNOT_E*
 */
int knot_rrset_synth_rrsig(const knot_rrset_t *rrsigs, uint16_t type, knot_rrset_t **out_sig,
                           mm_ctx_t *mm);

size_t knot_rrset_rr_count(const knot_rrset_t *rrset);

#endif /* _KNOT_RRSET_H_ */

/*! @} */
